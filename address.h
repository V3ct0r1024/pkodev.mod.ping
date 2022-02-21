#pragma once

namespace pkodev
{
	namespace address
	{
        // Game.exe 0 (1222073761)
        namespace GAME_13X_0
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x0067032C;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x00670354;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x00670358;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C5440;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C5DA0;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C4F0;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x0048FF80;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C4D40;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x00423FB0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C4E2B;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }

        // Game.exe 1 (1243412597)
        namespace GAME_13X_1
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x0067041C;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x00670444;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x00670448;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C5550;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C5EB0;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C4F0;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x00490090;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C4E50;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x00423FB0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C4F3B;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }

        // Game.exe 2 (1252912474)
        namespace GAME_13X_2
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x0067041C;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x00670444;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x00670448;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C55F0;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C5F50;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C4F0;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x00490130;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C4EF0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x00423FB0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C4FDB;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }

        // Game.exe 3 (1244511158)
        namespace GAME_13X_3
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x0067041C;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x00670444;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x00670448;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C55E0;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C5F40;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C4F0;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x00490120;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C4EE0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x00423FB0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C4FCB;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }

        // Game.exe 4 (1585009030)
        namespace GAME_13X_4
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x00670444;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x00670418;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x0067041C;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C57F0;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C6150;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C620;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x00490330;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C50F0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A748;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x004240E0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C51DB;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }

        // Game.exe 5 (1207214236)
        namespace GAME_13X_5
        {
            // CForm* CLoginScene::frmServer
            const unsigned int CLoginScene__frmServer = 0x00670334;

            // CListView* CLoginScene::lstServer[0];
            const unsigned int CLoginScene__lstServer_0 = 0x0067035C;

            // CListView* CLoginScene::lstServer[1];
            const unsigned int CLoginScene__lstServer_1 = 0x00670360;

            // void CLoginScene::_FrameMove(DWORD dwTimeParam)
            const unsigned int CLoginScene___FrameMove = 0x004C5270;

            // void CLoginScene::InitServerList(int nRegionNo)
            const unsigned int CLoginScene__InitServerList = 0x004C5BD0;

            // void CListItems::Render()
            const unsigned int CListItems__Render = 0x0042C4E0;

            // void CItem::Render( int x, int y )	
            const unsigned int CItem__Render = 0x0048FD80;

            // const char *SelectGroupIP(int nRegionNo, int nGroupNo)
            const unsigned int SelectGroupIP = 0x004C4B70;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A738;

            // void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
            const unsigned int CGuiFont__Render = 0x00423FA0;

            // inline const char* SelectGroupIP(int nRegionNo, int nGroupNo) patch
            // [E8 C0 62 0F 00] -> [B8 00 00 00 00]
            // CALL <address> ->  MOV EAX,0
            const unsigned int SelectGroupIP_Patch = 0x004C4C5B;

            // CServerSet
            const unsigned int CServerSet = 0x00660564;
        }
	}
}