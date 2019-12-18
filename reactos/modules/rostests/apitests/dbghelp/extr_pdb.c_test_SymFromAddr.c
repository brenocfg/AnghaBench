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
 int /*<<< orphan*/  ERROR_MOD_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INIT_PSYM (char*) ; 
 int MAX_SYM_NAME ; 
 int /*<<< orphan*/  SymFromAddr (int /*<<< orphan*/ ,int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  SymTagFunction ; 
 int /*<<< orphan*/  SymTagPublicSymbol ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_ulonglong (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  supports_pdb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_SymFromAddr(HANDLE hProc, DWORD64 BaseAddress)
{
    BOOL Ret;
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

    DWORD64 Displacement;
    DWORD dwErr;

    /* No address found before load address of module */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress -1, &Displacement, pSymbol);
    dwErr = GetLastError();
    ok_int(Ret, FALSE);
    ok_hex(dwErr, ERROR_MOD_NOT_FOUND);

    /* Right at the start of the module is recognized as the first symbol found */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0xffffffffffffffff);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "DllMain");

    /* The actual first instruction of the function */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress + 0x1010, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "DllMain");

    /* The last instruction in the function */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress + 0x102D, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0x1d);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "DllMain");

    /* The padding below the function */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress + 0x102E, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0x1e);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "DllMain");

    /* One byte before the next function */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress + 0x103f, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0x2f);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1010);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "DllMain");

    /* First byte of the next function */
    Displacement = 0;
    INIT_PSYM(buffer);
    Ret = SymFromAddr(hProc, BaseAddress + 0x1040, &Displacement, pSymbol);
    ok_int(Ret, TRUE);
    ok_ulonglong(Displacement, 0);
    ok_ulonglong(pSymbol->ModBase, BaseAddress);
    ok_hex(pSymbol->Flags, 0);
    ok_ulonglong(pSymbol->Address, BaseAddress + 0x1040);
    ok_hex(pSymbol->Tag, SymTagFunction);
    ok_str(pSymbol->Name, "FfsChkdsk");

    if (!supports_pdb(hProc, BaseAddress))
    {
        skip("dbghelp.dll too old or cannot read this symbol!\n");
    }
    else
    {
        /* .idata */
        Displacement = 0;
        INIT_PSYM(buffer);
        Ret = SymFromAddr(hProc, BaseAddress + 0x2000, &Displacement, pSymbol);
        ok_int(Ret, TRUE);
        ok_ulonglong(Displacement, 0);
        ok_ulonglong(pSymbol->ModBase, BaseAddress);
        ok_hex(pSymbol->Flags, 0);
        ok_ulonglong(pSymbol->Address, BaseAddress + 0x2000);
        ok_hex(pSymbol->Tag, SymTagPublicSymbol);
        ok_str(pSymbol->Name, "__imp__DbgPrint");
    }
}