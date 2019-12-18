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
struct TYPE_3__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Address; int /*<<< orphan*/  Flags; int /*<<< orphan*/  ModBase; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  SYMBOL_INFO ;
typedef  TYPE_1__* PSYMBOL_INFO ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD64 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_PSYM (char*) ; 
 int MAX_SYM_NAME ; 
 int /*<<< orphan*/  SymFromName (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int SymTagFunction ; 
 int SymTagPublicSymbol ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_ulonglong (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  supports_pdb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void test_SymFromName(HANDLE hProc, DWORD64 BaseAddress)
{
    BOOL Ret;
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

    if (!supports_pdb(hProc, BaseAddress))
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
}