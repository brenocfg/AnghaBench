#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SizeOfStruct; scalar_t__ ModBase; scalar_t__ Address; scalar_t__ MaxNameLen; } ;
typedef  int /*<<< orphan*/  SYMBOL_INFO ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSYMBOL_INFO ;
typedef  int /*<<< orphan*/  PIMAGE_NT_HEADERS ;
typedef  char* PCSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ImageNtHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageRvaToVa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_SYMBOL_NAME ; 
 int /*<<< orphan*/  SymFromName (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

PVOID
ImageSymToVa(HANDLE hProcess, PSYMBOL_INFO pSym, PBYTE pModule, PCSTR Name)
{
	PIMAGE_NT_HEADERS NtHeaders;
	PVOID p;

	pSym->SizeOfStruct = sizeof(SYMBOL_INFO);
	pSym->MaxNameLen = MAX_SYMBOL_NAME-1;

	if (!SymFromName(hProcess, Name, pSym))
	{
		printf("SymGetSymFromName64() failed: %ld\n", GetLastError());
		return 0;
	}
#if defined(__GNUC__) && \
	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40400)
	printf("looking up adress for %s: 0x%llx\n", Name, pSym->Address);
#else
	printf("looking up adress for %s: 0x%I64x\n", Name, pSym->Address);
#endif

	NtHeaders = ImageNtHeader(pModule);
	p = ImageRvaToVa(NtHeaders, pModule, pSym->Address - pSym->ModBase, NULL);

	return p;
}