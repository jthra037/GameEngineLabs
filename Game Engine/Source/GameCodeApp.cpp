#include "Headers\GameCodeApp.h"

GameCodeApp::GameCodeApp()
{
	InitInstance();
}

void GameCodeApp::InitInstance()
{
	std::cout << "Is Only Instance: " << IsOnlyInstance("CryptoNomenclature") << std::endl;
	std::cout << "More than 300MB space: " << CheckStorage(300) << std::endl;
	std::cout << "Available memory: ";
	CheckMemory();
	std::cout << std::endl;
	std::cout << "CPU Speed: " << ReadCPUSpeed() << std::endl;
}

bool GameCodeApp::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		//HWND hWnd = FindWindow(gameTitle, NULL);
		//if (hWnd) {
		//	// An instance of your game is already running. 
		//	ShowWindow(hWnd, SW_SHOWNORMAL);
		//	SetFocus(hWnd);
		//	SetForegroundWindow(hWnd);
		//	SetActiveWindow(hWnd);
		//	return false;
		//}
	}
	return true;
}

bool GameCodeApp::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk. 
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = diskSpaceNeeded /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if
		(diskfree.avail_clusters < neededClusters) {
		// if you get here you don’t have enough disk space! 
		//GCC_ERROR("CheckStorage Failure : Not enough physical storage.");
		std::cout << "CheckStorage Failure : Not enough physical storage." << std::endl;
		return false;
	}
	return true;
}

void GameCodeApp::CheckMemory()
{
	MEMORYSTATUSEX statex;
	GlobalMemoryStatusEx(&statex);

	std::cout << "Free physical memory: " << statex.ullAvailPhys << std::endl;
	std::cout << "Free virtual memory: " << statex.ullAvailVirtual << std::endl;
}

bool GameCodeApp::CheckMemory(const DWORDLONG physicalRAMNeeded,
	const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded) {
		/* you don’t have enough physical memory. Tell the
		player to go get a real computer and give this one to
		his mother.
		*/
		//GCC_ERROR("CheckMemory Failure : Not enough physical memory.");
		std::cout << "CheckMemory Failure : Not enough physical memory." << std::endl;
		return false;
	}
	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		// you don’t have enough virtual memory available.
		// Tell the player to shut down the copy of Visual Studio running in the background.
			//GCC_ERROR("CheckMemory Failure : Not enough virtual memory.");
		std::cout << "CheckMemory Failure : Not enough virtual memory." << std::endl;
		return false;
	}
	char *buff = new char[virtualRAMNeeded];
	if (buff)
		delete[] buff;
	else {
		// even though there is enough memory, it isn’t available in one block, which can be critical for games that manage their own memory
			//GCC_ERROR("CheckMemory Failure : Not enough contiguous memory.");
		std::cout << "CheckMemory Failure : Not enough contiguous memory." << std::endl;
		return false;
	}
}

DWORD GameCodeApp::ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden: 
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0,
		KEY_READ,
		&hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:  
		RegQueryValueEx(hKey,
			"~MHz",
			NULL,
			&type,
			(LPBYTE)&dwMHz,
			&BufSize);
	}
	return dwMHz;
}