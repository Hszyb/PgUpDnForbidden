// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#define _WIN32_WINNT  0x0500                   // 设置系统版本, 确保可以使用底层键盘钩子

typedef BOOL(CALLBACK* LPFNKEYBOARDPROC)(WPARAM, KBDLLHOOKSTRUCT*);


LPDWORD       g_lpdwVirtualKey = NULL;         // Keycode 数组的指针

int           g_nLength = 0;                   // Keycode 数组的大小

BOOL          g_bDisableKeyboard = FALSE;      // 是否屏蔽整个键盘

HINSTANCE     g_hInstance = NULL;              // 模块实例句柄

HHOOK         g_hHook = NULL;                  // 钩子句柄

LPFNKEYBOARDPROC   g_lpfnKeyboardProc;         // 键盘钩子回调函数指针





BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)

{

	// 保存模块实例句柄

	g_hInstance = (HINSTANCE)hModule;



	// 在进程结束或线程结束时卸载钩子

	switch (ul_reason_for_call)

	{

	case DLL_PROCESS_ATTACH:

		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_PROCESS_DETACH:



	case DLL_THREAD_DETACH:

		free(g_lpdwVirtualKey);

		if (g_hHook != NULL) UnhookWindowsHookEx(g_hHook);

		break;

	}

	return TRUE;

}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)

{

	// 拦截键盘的某些按键, 如果 g_bDisableKeyboard 为 TRUE 则拦截整个键盘按键

	if (nCode >= HC_ACTION)

	{

		KBDLLHOOKSTRUCT* pStruct = (KBDLLHOOKSTRUCT*)lParam;

		if (g_bDisableKeyboard)

		if (g_lpfnKeyboardProc(wParam, pStruct))

			return CallNextHookEx(g_hHook, nCode, wParam, lParam);

		else

			return true;



		LPDWORD tmpVirtualKey = g_lpdwVirtualKey;

		for (int i = 0; i < g_nLength; i++)

		{

			if (pStruct->vkCode == *tmpVirtualKey++)

			if (g_lpfnKeyboardProc(wParam, pStruct))

				return CallNextHookEx(g_hHook, nCode, wParam, lParam);

			else

				return true;

		}



	}



	// 调用系统中的下一个钩子

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);

}



/********************************************************************/

/* 开始拦截键盘按键                                                 */

/*                                                                  */

/* 参数:                                                            */

/*            lpdwVirtualKey              Keycode 数组的指针        */

/*            nLength                     Keycode 数组的大小        */

/*            bDisableKeyboard            是否拦截整个键盘          */

/*                                                                  */

/* 返回值:    TRUE 成功, FALSE 失败                                 */

/********************************************************************/

BOOL WINAPI StartMaskKey(LPDWORD lpdwVirtualKey, int nLength,

	LPFNKEYBOARDPROC lpfnKeyboardProc, BOOL bDisableKeyboard = FALSE)

{

	// 如果已经安装键盘钩子则返回 FALSE

	if (g_hHook != NULL || nLength == 0) return FALSE;



	// 将用户传来的 keycode 数组保存在全局变量中

	g_lpdwVirtualKey = (LPDWORD)malloc(sizeof(DWORD)* nLength);

	LPDWORD tmpVirtualKey = g_lpdwVirtualKey;

	for (int i = 0; i < nLength; i++)

	{

		*tmpVirtualKey++ = *lpdwVirtualKey++;

	}

	g_nLength = nLength;

	g_bDisableKeyboard = bDisableKeyboard;

	g_lpfnKeyboardProc = lpfnKeyboardProc;



	// 安装底层键盘钩子

	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInstance, NULL);

	if (g_hHook == NULL) return FALSE;

	return TRUE;



}



/********************************************************************/

/* 停止拦截键盘按键                                                 */

/*                                                                  */

/* 参数: (无)                                                       */

/*                                                                  */

/* 返回值:    TRUE 成功, FALSE 失败                                 */

/********************************************************************/

BOOL WINAPI StopMaskKey()

{

	// 卸载钩子

	if (UnhookWindowsHookEx(g_hHook) == 0) return FALSE;

	g_hHook = NULL;

	return TRUE;

}
