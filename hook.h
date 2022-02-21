#pragma once
#include "structure.h"

namespace pkodev
{
	namespace hook
	{
		// void CLoginScene::_FrameMove(DWORD dwTimeParam)
		void __fastcall CLoginScene___FrameMove(void* This, void* NotUsed, unsigned int dwTimeParam);

		// void CLoginScene::InitServerList(int nRegionNo)
		void __fastcall CLoginScene__InitServerList(void* This, void* NotUsed,  int nRegionNo);

		// void CListItems::Render()
		void __fastcall CListItems__Render(void* This, void* NotUsed);

		// void CItem::Render( int x, int y )
		void __fastcall CItem__Render(void* This, void* NotUsed, int x, int y);
	}
}