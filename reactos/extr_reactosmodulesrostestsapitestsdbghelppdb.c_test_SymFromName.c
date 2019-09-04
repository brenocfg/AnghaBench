#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ModBase; int Address; int /*<<< orphan*/  Name; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  SYMBOL_INFO ;
typedef  TYPE_1__* PSYMBOL_INFO ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD64 ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INIT_PSYM (char*) ; 
 int MAX_SYM_NAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SymFromName (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int SymLoadModule64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int SymTagFunction ; 
 int SymTagPublicSymbol ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  can_enumerate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  deinit_sym () ; 
 int /*<<< orphan*/  init_sym () ; 
 int /*<<< orphan*/  ok_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_ulonglong (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_SymFromName(HANDLE hProc, const char* szModuleName)
{
    BOOL Ret;
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

    DWORD64 BaseAddress;
    DWORD dwErr;

    if (!init_sym())
        return;

    SetLastError(ERROR_SUCCESS);
    BaseAddress = SymLoadModule64(hProc, NULL, szModuleName, NULL, 0x600000, 0);
    dwErr = GetLastError();

    ok_ulonglong(BaseAddress, 0x600000);
    ok_hex(dwErr, ERROR_SUCCESS);

    if (!can_enumerate(hProc, BaseAddress))
    {
        skip("dbghelp.dll too old or cannot enumerate symbols!\n");
    }
    else
    {
        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "DllMain", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0);
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
        ok_hex(pSymbol->Tag, SymTagFunction);
        ok_str(pSymbol->Name, "DllMain");

        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "_DllMain@12", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0x400000);   // ??
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
        ok_hex(pSymbol->Tag, SymTagPublicSymbol);
        ok_str(pSymbol->Name, "_DllMain@12");

        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "FfsChkdsk", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0);
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1040);
        ok_hex(pSymbol->Tag, SymTagFunction);
        ok_str(pSymbol->Name, "FfsChkdsk");

        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "_FfsChkdsk@24", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0x400000);   // ??
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1040);
        ok_hex(pSymbol->Tag, SymTagPublicSymbol);
        ok_str(pSymbol->Name, "_FfsChkdsk@24");

        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "FfsFormat", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0);
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1070);
        ok_hex(pSymbol->Tag, SymTagFunction);
        ok_str(pSymbol->Name, "FfsFormat");

        INIT_PSYM(buffer);
        Ret = SymFromName(hProc, "_FfsFormat@24", pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0x400000);   // ??
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x1070);
        ok_hex(pSymbol->Tag, SymTagPublicSymbol);
        ok_str(pSymbol->Name, "_FfsFormat@24");
    }

    deinit_sym();
}