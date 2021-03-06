#pragma once
#include <Windows.h>
#include <direct.h>
#include <iostream>
#include <string>

class GameCodeApp
{
	public:
		GameCodeApp();
	private:
		void InitInstance();
		bool IsOnlyInstance(LPCTSTR gameTitle);
		bool CheckStorage(const DWORDLONG diskSpaceNeeded);
		void CheckMemory();
		bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
		DWORD ReadCPUSpeed();
		std::string ReadCPUArchitecture();
};