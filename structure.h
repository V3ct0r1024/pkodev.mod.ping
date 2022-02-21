#pragma once
#include <string>
#include <vector>

namespace pkodev
{
    // Ping proccess stages
    enum class ping_stage_t : unsigned int
    {
        start,
        wait,
        done,
    };

    // Colors of latency labels
    enum class latency_color_t : unsigned int
    {
        // 0 - 50
        min = 0xFF03C03C,    // Green

        // 51 - 100
        avg = 0xFFFF8000,    // Orange

        // 101 - -//-
        max = 0xFFFF0000,    // Red

        // Offline
        offline = 0xFF5F5F5F // Gray
    };

    // List of servers currently being rendered 
    enum class list_t : unsigned int
    {
        lvUnknown = 0,
        lvServer0 = 1,
        lvServer1 = 2
    };

    // Ping data
    struct ping final
    {
        // IP address
        std::string ip;

        // Online
        bool online;

        // Ping (ms)
        unsigned int latency;

        // Is the IP address is already pinged
        bool done;

        // Ping event
        HANDLE event;

        // ICMP handle
        HANDLE icmp;

        // Size of the request buffer
        static const WORD request_size{ 5 };

        // Request buffer
        char request[request_size]{"ping"};

        // Size of the response buffer
        static const WORD response_size{ sizeof(ICMP_ECHO_REPLY) + request_size + 8 };

        // Response buffer
        char response[response_size];

        // Constructor
        ping() :
            ip(""),
            online(false),
            latency(0),
            done(false),
            event(NULL),
            icmp(NULL)
        {
            std::memset(reinterpret_cast<void*>(request), 0x00, request_size);
            std::memset(reinterpret_cast<void*>(response), 0x00, response_size);
        }

        // Constructor
        ping(const std::string& ip_) :
            ip(ip_),
            online(false),
            latency(0),
            done(false),
            event(NULL),
            icmp(NULL)
        {
            std::memset(reinterpret_cast<void*>(request), 0x00, request_size);
            std::memset(reinterpret_cast<void*>(response), 0x00, response_size);
        }
    };

    // Multiple ping process data
    struct ping_process final
    {
        // The number of IP addresses to ping
        unsigned int counter;

        // The number of IP addresses are already pinged
        unsigned int done;

        // The current stage
        ping_stage_t stage;

        // List of IP addresses to ping
        std::vector<ping> arr;

        // Constructor
        ping_process() :
            counter(0),
            done(0),
            stage(ping_stage_t::start)
        {
            arr.reserve(8);
        }
    } proccess;

    // Data associated with the work of the client GUI 
    struct gui_data final
    {
        // State of the form frmServer, displayed or hidden
        bool frmServer_IsShowing;

        // List of servers currently being rendered
        list_t current_list;

        // Index of the current element in the list of servers being rendered
        unsigned int index;


        // Constructor
        gui_data() :
            frmServer_IsShowing(false),
            current_list(list_t::lvUnknown),
            index(0)
        {

        }
    } gui;
}