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
struct sym_enum {scalar_t__ buffer; scalar_t__ sym_info; scalar_t__ addr; scalar_t__ tag; scalar_t__ index; int /*<<< orphan*/  user; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PSYM_ENUMERATESYMBOLS_CALLBACK ;
typedef  scalar_t__ PSYMBOL_INFO ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  sym_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sym_enum*) ; 

__attribute__((used)) static inline BOOL doSymEnumSymbols(HANDLE hProcess, ULONG64 BaseOfDll, PCWSTR Mask,
                                    PSYM_ENUMERATESYMBOLS_CALLBACK EnumSymbolsCallback,
                                    PVOID UserContext)
{
    struct sym_enum     se;

    se.cb = EnumSymbolsCallback;
    se.user = UserContext;
    se.index = 0;
    se.tag = 0;
    se.addr = 0;
    se.sym_info = (PSYMBOL_INFO)se.buffer;

    return sym_enum(hProcess, BaseOfDll, Mask, &se);
}