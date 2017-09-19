#pragma once
#include <Windows.h>
#include <direct.h>
#include <iostream>

class GameCodeApp
{
	public:
		GameCodeApp();
	private:
		void InitInstance();
		bool IsOnlyInstance(LPCTSTR gameTitle);
		bool CheckStorage(const DWORDLONG diskSpaceNeeded);
		bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
};