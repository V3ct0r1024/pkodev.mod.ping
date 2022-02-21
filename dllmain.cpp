#include <vector>
#include <cstdio>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <detours.h>

#include "loader.h"

#include "address.h"
#include "pointer.h"
#include "hook.h"
#include "structure.h"



namespace pkodev
{
    // Ping interval in milliseconds
    const unsigned int ping_period = 3000; // 3 seconds

    // Ping timer
    unsigned int timer = 0;
}

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Patch the function inline const char* SelectGroupIP(int nRegionNo, int nGroupNo)
    {
        // Patch bytes
        const char patch_bytes[] = { (char)0xB8, (char)0x00, (char)0x00, (char)0x00, (char)0x00 };

        // Access type
        DWORD access = PAGE_EXECUTE_READWRITE;

        // Change the access protection of the proccess
        VirtualProtect(reinterpret_cast<LPVOID>(pkodev::address::MOD_EXE_VERSION::SelectGroupIP_Patch),
            sizeof(patch_bytes), access, &access);

        // Write patch bytes
        WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(pkodev::address::MOD_EXE_VERSION::SelectGroupIP_Patch),
            reinterpret_cast<LPCVOID>(patch_bytes), sizeof(patch_bytes), nullptr);

        // Rollback the access protection of the proccess
        VirtualProtect(reinterpret_cast<LPVOID>(pkodev::address::MOD_EXE_VERSION::SelectGroupIP_Patch),
            sizeof(patch_bytes), access, &access);
    }

    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CLoginScene___FrameMove, pkodev::hook::CLoginScene___FrameMove);
    DetourAttach(&(PVOID&)pkodev::pointer::CLoginScene__InitServerList, pkodev::hook::CLoginScene__InitServerList);
    DetourAttach(&(PVOID&)pkodev::pointer::CListItems__Render, pkodev::hook::CListItems__Render);
    DetourAttach(&(PVOID&)pkodev::pointer::CItem__Render, pkodev::hook::CItem__Render);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CLoginScene___FrameMove, pkodev::hook::CLoginScene___FrameMove);
    DetourDetach(&(PVOID&)pkodev::pointer::CLoginScene__InitServerList, pkodev::hook::CLoginScene__InitServerList);
    DetourDetach(&(PVOID&)pkodev::pointer::CListItems__Render, pkodev::hook::CListItems__Render);
    DetourDetach(&(PVOID&)pkodev::pointer::CItem__Render, pkodev::hook::CItem__Render);
    DetourTransactionCommit();
}

// void CLoginScene::_FrameMove(DWORD dwTimeParam)
void __fastcall pkodev::hook::CLoginScene___FrameMove(void* This, void* NotUsed, 
    unsigned int dwTimeParam)
{
    // Call the original method void CLoginScene::_FrameMove(DWORD dwTimeParam)
    pkodev::pointer::CLoginScene___FrameMove(This, dwTimeParam);
    
    // Get the current state of the form frmServer, displayed or hidden
    pkodev::gui.frmServer_IsShowing = *reinterpret_cast<bool*>(
        *reinterpret_cast<unsigned int*>(
            pkodev::address::MOD_EXE_VERSION::CLoginScene__frmServer
        ) + 0x4C
    );

    // Check that server list is showing
    if (pkodev::gui.frmServer_IsShowing == true)
    {
        // Calculate the time delta since the last update
        unsigned int delta = (dwTimeParam - pkodev::timer);

        // Check that some time passed
        if ( delta < pkodev::ping_period && pkodev::timer != 0 )
        { 
            // Waiting . . .
            return; 
        }

        // Handle the current ping stage
        switch (pkodev::proccess.stage)
        {
            // Start ping process
            case pkodev::ping_stage_t::start:
                {
                    // Reset the number of IP addresses to ping
                    pkodev::proccess.counter = 0;

                    // Start the ping proccess for all IP addresses
                    for (auto& p : pkodev::proccess.arr)
                    {
                        // Reset the done flag
                        p.done = true;

                        // Convert the IP address
                        IPAddr ip_addr;
                        if (inet_pton(AF_INET, p.ip.c_str(), &ip_addr) != 1)
                        {
                            // Unable to convert given ip address
                            continue;
                        }

                        // Open ICMP handle
                        if ( (p.icmp = IcmpCreateFile()) == INVALID_HANDLE_VALUE )
                        {
                            // Unable to open handle
                            continue;
                        }

                        // Create response event
                        if ( (p.event = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL )
                        {
                            // Unable to create event
                            IcmpCloseHandle(p.icmp);
                            continue;
                        }

                        // Start ping
                        DWORD ret = IcmpSendEcho2(
                            p.icmp, p.event, NULL, NULL, ip_addr,
                            p.request, p.request_size, NULL,
                            p.response, p.response_size, 1000
                        );

                        // Check the result
                        if (ret == 0)
                        {
                            // Check that ping operation is pending
                            if (GetLastError() != ERROR_IO_PENDING)
                            {
                                // Error
                                IcmpCloseHandle(p.icmp);
                                CloseHandle(p.event);

                                continue;
                            }
                        }

                        // Success
                        p.done = false;

                        // Increase the number of IP addresses to ping
                        pkodev::proccess.counter++;
                    }

                    // Reset the number of IP addresses are already pinged
                    pkodev::proccess.done = 0;

                    // Go to the next stage
                    pkodev::proccess.stage = pkodev::ping_stage_t::wait;
                }
                break;

            case pkodev::ping_stage_t::wait:
                {
                    // Check that ping proccess is done
                    for (auto& p : pkodev::proccess.arr)
                    {
                        // Check that the current IP address is not pinged yet
                        if (p.done == true)
                        {
                            continue;
                        }

                        // Check ping event
                        const DWORD ret = WaitForSingleObject(p.event, 0);

                        // Check the result
                        switch (ret)
                        {
                            // Ping is done
                            case WAIT_OBJECT_0:
                            {
                                // Get response data
                                PICMP_ECHO_REPLY pEchoReply = reinterpret_cast<PICMP_ECHO_REPLY>(p.response);

                                // Check eror status
                                if (pEchoReply->Status == IP_SUCCESS)
                                {
                                    // Success!
                                    p.online = true;
                                    p.latency = static_cast<unsigned int>(pEchoReply->RoundTripTime);
                                }
                                else
                                {
                                    // Error!
                                    p.online = false;
                                    p.latency = 0;
                                }

                                // Raise the done flag
                                p.done = true;
                            }
                            break;

                            // Wait . . . 
                            case WAIT_TIMEOUT:

                                break;

                                // Error . . .
                            case WAIT_FAILED:
                            case WAIT_ABANDONED:

                                // Raise the done flag
                                p.done = true;

                                break;
                        }

                        // Check that this IP address is checked
                        if (p.done == true)
                        {
                            // Increase the number of IP addresses are already pinged
                            pkodev::proccess.done++;

                            // Close the event handle
                            CloseHandle(p.event);

                            // Close the ICMP handle
                            IcmpCloseHandle(p.icmp);
                        }
                    }

                    // Check that all IP addresses are checked
                    if (pkodev::proccess.counter == pkodev::proccess.done)
                    {
                        // Go to the next stage
                        pkodev::proccess.stage = ping_stage_t::done;
                    }
                }
                break;

            case pkodev::ping_stage_t::done:

                // Set timer
                pkodev::timer = dwTimeParam;

                // Nothing to do... Go to the next stage!
                pkodev::proccess.stage = pkodev::ping_stage_t::start;

                break;
        }
    }
    else
    {
        // Check current ping proccess stage
        if (pkodev::proccess.stage == pkodev::ping_stage_t::wait)
        {
            // Close all active handles
            for (auto& p : pkodev::proccess.arr)
            {
                // Check the status of the current IP address
                if (p.done == true)
                {
                    // Error or pinged - handles are already closed
                    continue;
                }

                // Close event handle
                CloseHandle(p.event);

                // Close the ICMP handle
                IcmpCloseHandle(p.icmp);
            }

            // Go to stage 1
            pkodev::proccess.stage = pkodev::ping_stage_t::start;
        }
    }
}

// void CLoginScene::InitServerList(int nRegionNo)
void __fastcall pkodev::hook::CLoginScene__InitServerList(void* This, void* NotUsed, 
    int nRegionNo)
{
    // Get the number of servers in the current region
    const unsigned int count = *reinterpret_cast<unsigned int*>(
        *reinterpret_cast<unsigned int*>(pkodev::address::MOD_EXE_VERSION::CServerSet)
            + nRegionNo * 4 + 0x06D0
    );

    // Reset the timer
    pkodev::timer = 0;
    
    // Remove the old ip addresses list
    pkodev::proccess.arr.clear();

    // Make the new IP addresses list
    for (unsigned int i = 0; i < count; ++i)
    {
        pkodev::proccess.arr.push_back(
            { pkodev::pointer::SelectGroupIP(nRegionNo, i) }
        );
    }

    // Call the original method void CLoginScene::InitServerList(int nRegionNo)
    pkodev::pointer::CLoginScene__InitServerList(This, nRegionNo);
}

// void CListItems::Render()
void __fastcall pkodev::hook::CListItems__Render(void* This, void* NotUsed)
{
    // Check that server list is showing
    if (pkodev::gui.frmServer_IsShowing == true)
    {
        // Get pointer to the list
        auto get_listview_ptr = [](unsigned int addr_) -> void *
        {
            return reinterpret_cast<void*>(
                *reinterpret_cast<unsigned int*>(
                    *reinterpret_cast<unsigned int*>(
                        *reinterpret_cast<unsigned int*>(
                            addr_
                        ) + 0xA0
                    ) + 0x0A4
                )
            );
        };

        // Determine the current GUI list: lstServer0 or lstServer1
        const pkodev::list_t list = (
            (get_listview_ptr(pkodev::address::MOD_EXE_VERSION::CLoginScene__lstServer_0) == This) ? pkodev::list_t::lvServer0 :
            (get_listview_ptr(pkodev::address::MOD_EXE_VERSION::CLoginScene__lstServer_1) == This) ? pkodev::list_t::lvServer1 :
            pkodev::list_t::lvUnknown
        );

        // Check if the servers list has changed
        if (list != pkodev::gui.current_list)
        {
            // Set the new current servers list
            pkodev::gui.current_list = list;

            // Reset the current item index
            pkodev::gui.index = 0;
        }
    }

    // Call the original method void CListItems::Render()
    pkodev::pointer::CListItems__Render(This);
}

// void CItem::Render( int x, int y )
void __fastcall pkodev::hook::CItem__Render(void* This, void* NotUsed, int x, int y)
{
    // Check that server list is showing
    if (pkodev::gui.frmServer_IsShowing == true)
    {
        // Get the caption from CItem object
        auto get_caption = [](void *CItem_) -> const char *
        {
            // Pointer to the string
            const char* caption = nullptr;

            // Get the pointer
            if (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(CItem_) + 0x1C) < 0x10)
            {
                caption = reinterpret_cast<const char*>(
                    reinterpret_cast<unsigned int>(CItem_) + 0x08
                );
            }
            else 
            {
                caption = *reinterpret_cast<const char**>(
                    reinterpret_cast<unsigned int>(CItem_) + 0x08
                );
            }

            return caption;
        };

        // Get the IP address of the server
        auto get_ip = []() -> const char *
        {
            // Get ip index
            unsigned int ip_index = ( 
                (pkodev::gui.current_list == pkodev::list_t::lvServer0) ?
                    (pkodev::gui.index * 2) : (pkodev::gui.index * 2 + 1)
            );

            // Check the index
            if ( ip_index >= pkodev::proccess.arr.size() )
            {
                // Index is out of bounds
                return nullptr;
            }
            
            return pkodev::proccess.arr[ip_index].ip.c_str();
        };

        // Render the server name
        pkodev::pointer::CGuiFont_Render(
            reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CGuiFont),
            get_caption(This), x, y,
            *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(This) + 0x20)
        );

        // Get current IP address
        const char* ip = get_ip();

        // Increase the current item index
        pkodev::gui.index++;

        // Check the IP address
        if (ip == nullptr)
        {
            // Exit from the hook
            return;
        }
        
        // Search the IP address in the list
        const auto it = std::find_if(
            pkodev::proccess.arr.begin(),
            pkodev::proccess.arr.end(),
            [&ip](const ping& p) -> bool
            {
                return ( strcmp( ip, p.ip.c_str() ) == 0 );
            }
        );

        // Check that IP address is found
        if ( it != pkodev::proccess.arr.end() )
        {
            // Buffer for the latency label
            static char buf[32]{ 0x00 };

            // Color of the latency label
            unsigned int color = 0xFF000000;

            // Check that server is online
            if (it->online == true)
            {
                // Determine the color of latency the label
                color = static_cast<unsigned int>(
                    (it->latency <= 50) ? pkodev::latency_color_t::min :
                        (it->latency <= 100) ? pkodev::latency_color_t::avg : pkodev::latency_color_t::max
                );

                // Build the ping label
                sprintf_s(buf, sizeof(buf), "[%dms]", it->latency);
            }
            else
            {
                // Set offline color
                color = static_cast<unsigned int>(pkodev::latency_color_t::offline);

                // Build the ping label
                sprintf_s(buf, sizeof(buf), "[-]");
            }

            // Get the list item width
            const unsigned int width = *reinterpret_cast<unsigned int*>(
                *reinterpret_cast<unsigned int*>(
                    *reinterpret_cast<unsigned int*>(
                        (pkodev::gui.current_list == pkodev::list_t::lvServer0) ?
                            pkodev::address::MOD_EXE_VERSION::CLoginScene__lstServer_0 :
                            pkodev::address::MOD_EXE_VERSION::CLoginScene__lstServer_1
                    ) + 0xA0
                ) + 0x2C
            );

            // Calculate the position of the label
            x = (x + width) - 72;
            y = y;

            // Render the ping label
            pkodev::pointer::CGuiFont_Render( 
                reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CGuiFont), 
                buf, x, y,  color 
            );
         }
    }
    else
    {
        // Call the original method void CItem::Render( int x, int y )
        pkodev::pointer::CItem__Render(This, x, y);
    }
}