#pragma once
#include "address.h"
#include "structure.h"

namespace pkodev
{
	namespace pointer
	{
		// void CLoginScene::_FrameMove(DWORD dwTimeParam)
		typedef void(__thiscall* CLoginScene___FrameMove__Ptr)(void*, unsigned int);
		CLoginScene___FrameMove__Ptr CLoginScene___FrameMove = (CLoginScene___FrameMove__Ptr)(void*)(address::MOD_EXE_VERSION::CLoginScene___FrameMove);
		
		// void CLoginScene::InitServerList(int nRegionNo)
		typedef void(__thiscall* CCLoginScene__InitServerList__Ptr)(void*, int);
		CCLoginScene__InitServerList__Ptr CLoginScene__InitServerList = (CCLoginScene__InitServerList__Ptr)(void*)(address::MOD_EXE_VERSION::CLoginScene__InitServerList);

		// void CListItems::Render()
		typedef void(__thiscall* CListItems__Render__Ptr)(void*);
		CListItems__Render__Ptr CListItems__Render = (CListItems__Render__Ptr)(void*)(address::MOD_EXE_VERSION::CListItems__Render);

		// void CItem::Render( int x, int y )	
		typedef void(__thiscall* CItem__Render__Ptr)(void*, int, int);
		CItem__Render__Ptr CItem__Render = (CItem__Render__Ptr)(void*)(address::MOD_EXE_VERSION::CItem__Render);
		
		// const char *SelectGroupIP(int nRegionNo, int nGroupNo)
		typedef const char*(__cdecl* SelectGroupIP__Ptr)(int, int);
		SelectGroupIP__Ptr SelectGroupIP = (SelectGroupIP__Ptr)(void*)(address::MOD_EXE_VERSION::SelectGroupIP);

		// void CGuiFont::Render( const char* str, int x, int y, DWORD color,float size )
		typedef void(__thiscall* CGuiFont_Render_Ptr)(void*, const char*, int, int, unsigned int);
		CGuiFont_Render_Ptr CGuiFont_Render = (CGuiFont_Render_Ptr)(void*)(address::MOD_EXE_VERSION::CGuiFont__Render);
	}
}