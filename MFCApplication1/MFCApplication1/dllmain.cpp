// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#define _WIN32_WINNT  0x0500                   // ����ϵͳ�汾, ȷ������ʹ�õײ���̹���

typedef BOOL(CALLBACK* LPFNKEYBOARDPROC)(WPARAM, KBDLLHOOKSTRUCT*);


LPDWORD       g_lpdwVirtualKey = NULL;         // Keycode �����ָ��

int           g_nLength = 0;                   // Keycode ����Ĵ�С

BOOL          g_bDisableKeyboard = FALSE;      // �Ƿ�������������

HINSTANCE     g_hInstance = NULL;              // ģ��ʵ�����

HHOOK         g_hHook = NULL;                  // ���Ӿ��

LPFNKEYBOARDPROC   g_lpfnKeyboardProc;         // ���̹��ӻص�����ָ��





BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)

{

	// ����ģ��ʵ�����

	g_hInstance = (HINSTANCE)hModule;



	// �ڽ��̽������߳̽���ʱж�ع���

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

	// ���ؼ��̵�ĳЩ����, ��� g_bDisableKeyboard Ϊ TRUE �������������̰���

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



	// ����ϵͳ�е���һ������

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);

}



/********************************************************************/

/* ��ʼ���ؼ��̰���                                                 */

/*                                                                  */

/* ����:                                                            */

/*            lpdwVirtualKey              Keycode �����ָ��        */

/*            nLength                     Keycode ����Ĵ�С        */

/*            bDisableKeyboard            �Ƿ�������������          */

/*                                                                  */

/* ����ֵ:    TRUE �ɹ�, FALSE ʧ��                                 */

/********************************************************************/

BOOL WINAPI StartMaskKey(LPDWORD lpdwVirtualKey, int nLength,

	LPFNKEYBOARDPROC lpfnKeyboardProc, BOOL bDisableKeyboard = FALSE)

{

	// ����Ѿ���װ���̹����򷵻� FALSE

	if (g_hHook != NULL || nLength == 0) return FALSE;



	// ���û������� keycode ���鱣����ȫ�ֱ�����

	g_lpdwVirtualKey = (LPDWORD)malloc(sizeof(DWORD)* nLength);

	LPDWORD tmpVirtualKey = g_lpdwVirtualKey;

	for (int i = 0; i < nLength; i++)

	{

		*tmpVirtualKey++ = *lpdwVirtualKey++;

	}

	g_nLength = nLength;

	g_bDisableKeyboard = bDisableKeyboard;

	g_lpfnKeyboardProc = lpfnKeyboardProc;



	// ��װ�ײ���̹���

	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInstance, NULL);

	if (g_hHook == NULL) return FALSE;

	return TRUE;



}



/********************************************************************/

/* ֹͣ���ؼ��̰���                                                 */

/*                                                                  */

/* ����: (��)                                                       */

/*                                                                  */

/* ����ֵ:    TRUE �ɹ�, FALSE ʧ��                                 */

/********************************************************************/

BOOL WINAPI StopMaskKey()

{

	// ж�ع���

	if (UnhookWindowsHookEx(g_hHook) == 0) return FALSE;

	g_hHook = NULL;

	return TRUE;

}
