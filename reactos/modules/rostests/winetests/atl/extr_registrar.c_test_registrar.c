#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IRegistrar ;
typedef  int INT ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_Registrar ; 
 int /*<<< orphan*/  CP_ACP ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int ERROR_SUCCESS ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IRegistrar ; 
 int /*<<< orphan*/  IRegistrar_Release (int /*<<< orphan*/ *) ; 
 int IRegistrar_StringRegister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IRegistrar_StringUnregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  textA ; 
 int /*<<< orphan*/  win_skip (char*,...) ; 

__attribute__((used)) static void test_registrar(void)
{
    IRegistrar *registrar = NULL;
    HRESULT hr;
    INT count;
    WCHAR *textW = NULL;

    if (!GetProcAddress(GetModuleHandleA("atl.dll"), "AtlAxAttachControl"))
    {
        win_skip("Old versions of atl.dll don't support binary values\n");
        return;
    }

    hr = CoCreateInstance(&CLSID_Registrar, NULL, CLSCTX_INPROC_SERVER, &IID_IRegistrar, (void**)&registrar);
    if (FAILED(hr))
    {
        win_skip("creating IRegistrar failed, hr = 0x%08X\n", hr);
        return;
    }

    count = MultiByteToWideChar(CP_ACP, 0, textA, -1, NULL, 0);
    textW = HeapAlloc(GetProcessHeap(), 0, count * sizeof(WCHAR));
    if (textW)
    {
        DWORD dword;
        DWORD size;
        LONG lret;
        HKEY key;
        BYTE bytes[4];

        MultiByteToWideChar(CP_ACP, 0, textA, -1, textW, count);
        hr = IRegistrar_StringRegister(registrar, textW);
        ok(hr == S_OK, "StringRegister failed: %08x\n", hr);
        if (FAILED(hr))
        {
            IRegistrar_Release(registrar);
            return;
        }

        lret = RegOpenKeyA(HKEY_CURRENT_USER, "eebf73c4-50fd-478f-bbcf-db212221227a", &key);
        ok(lret == ERROR_SUCCESS, "error %d opening registry key\n", lret);

        size = sizeof(dword);
        lret = RegQueryValueExA(key, "dword_unquoted_hex", NULL, NULL, (BYTE*)&dword, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueExA failed, error %d\n", lret);
        ok(dword != 0xA, "unquoted hex is not supposed to be preserved\n");

        size = sizeof(dword);
        lret = RegQueryValueExA(key, "dword_quoted_hex", NULL, NULL, (BYTE*)&dword, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueExA failed, error %d\n", lret);
        ok(dword != 0xA, "quoted hex is not supposed to be preserved\n");

        size = sizeof(dword);
        lret = RegQueryValueExA(key, "dword_unquoted_dec", NULL, NULL, (BYTE*)&dword, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueExA failed, error %d\n", lret);
        ok(dword == 1, "unquoted dec is not supposed to be %d\n", dword);

        size = sizeof(dword);
        lret = RegQueryValueExA(key, "dword_quoted_dec", NULL, NULL, (BYTE*)&dword, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueExA failed, error %d\n", lret);
        ok(dword == 1, "quoted dec is not supposed to be %d\n", dword);

        size = 4;
        lret = RegQueryValueExA(key, "binary_quoted", NULL, NULL, bytes, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueA, failed, error %d\n", lret);
        ok(bytes[0] == 0xde && bytes[1] == 0xad && bytes[2] == 0xbe && bytes[3] == 0xef,
            "binary quoted value was not preserved (it's 0x%02X%02X%02X%02X)\n",
            0xff & bytes[0], 0xff & bytes[1], 0xff & bytes[2], 0xff & bytes[3]);

        size = 4;
        lret = RegQueryValueExA(key, "binary_unquoted", NULL, NULL, bytes, &size);
        ok(lret == ERROR_SUCCESS, "RegQueryValueA, failed, error %d\n", lret);
        ok(bytes[0] == 0xde && bytes[1] == 0xad && bytes[2] == 0xbe && bytes[3] == 0xef,
            "binary unquoted value was not preserved (it's 0x%02X%02X%02X%02X)\n",
            0xff & bytes[0], 0xff & bytes[1], 0xff & bytes[2], 0xff & bytes[3]);

        hr = IRegistrar_StringUnregister(registrar, textW);
        ok(SUCCEEDED(hr), "IRegistrar_StringUnregister failed, hr = 0x%08X\n", hr);
        RegCloseKey(key);

        HeapFree(GetProcessHeap(), 0, textW);
    }
    else
        skip("allocating memory failed\n");

    IRegistrar_Release(registrar);
}