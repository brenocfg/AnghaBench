#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sym_enum {int dummy; } ;
struct module_pair {TYPE_2__* pcs; TYPE_5__* requested; } ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_8__ {int /*<<< orphan*/  ModuleName; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ module; struct TYPE_10__* next; } ;
struct TYPE_9__ {TYPE_5__* lmodules; } ;
typedef  scalar_t__ const* PCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DMT_ELF ; 
 scalar_t__ DMT_MACHO ; 
 scalar_t__ DMT_PE ; 
 int /*<<< orphan*/  DMT_UNKNOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int SYMOPT_WINE_WITH_NATIVE_MODULES ; 
 scalar_t__ SymMatchStringW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int dbghelp_options ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 TYPE_5__* module_find_by_addr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_get_containee (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ module_get_debug (struct module_pair*) ; 
 TYPE_2__* process_find_by_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ const* starW ; 
 scalar_t__* strchrW (scalar_t__ const*,char) ; 
 int /*<<< orphan*/  symt_enum_locals (TYPE_2__*,scalar_t__ const*,struct sym_enum const*) ; 
 scalar_t__ symt_enum_module (struct module_pair*,scalar_t__ const*,struct sym_enum const*) ; 

__attribute__((used)) static BOOL sym_enum(HANDLE hProcess, ULONG64 BaseOfDll, PCWSTR Mask,
                     const struct sym_enum* se)
{
    struct module_pair  pair;
    const WCHAR*        bang;
    WCHAR*              mod;

    pair.pcs = process_find_by_handle(hProcess);
    if (!pair.pcs) return FALSE;
    if (BaseOfDll == 0)
    {
        /* do local variables ? */
        if (!Mask || !(bang = strchrW(Mask, '!')))
            return symt_enum_locals(pair.pcs, Mask, se);

        if (bang == Mask) return FALSE;

        mod = HeapAlloc(GetProcessHeap(), 0, (bang - Mask + 1) * sizeof(WCHAR));
        if (!mod) return FALSE;
        memcpy(mod, Mask, (bang - Mask) * sizeof(WCHAR));
        mod[bang - Mask] = 0;

        for (pair.requested = pair.pcs->lmodules; pair.requested; pair.requested = pair.requested->next)
        {
            if (pair.requested->type == DMT_PE && module_get_debug(&pair))
            {
                if (SymMatchStringW(pair.requested->module.ModuleName, mod, FALSE) &&
                    symt_enum_module(&pair, bang + 1, se))
                    break;
            }
        }
        /* not found in PE modules, retry on the ELF ones
         */
        if (!pair.requested && (dbghelp_options & SYMOPT_WINE_WITH_NATIVE_MODULES))
        {
            for (pair.requested = pair.pcs->lmodules; pair.requested; pair.requested = pair.requested->next)
            {
                if ((pair.requested->type == DMT_ELF || pair.requested->type == DMT_MACHO) &&
                    !module_get_containee(pair.pcs, pair.requested) &&
                    module_get_debug(&pair))
                {
                    if (SymMatchStringW(pair.requested->module.ModuleName, mod, FALSE) &&
                        symt_enum_module(&pair, bang + 1, se))
                    break;
                }
            }
        }
        HeapFree(GetProcessHeap(), 0, mod);
        return TRUE;
    }
    pair.requested = module_find_by_addr(pair.pcs, BaseOfDll, DMT_UNKNOWN);
    if (!module_get_debug(&pair))
        return FALSE;

    /* we always ignore module name from Mask when BaseOfDll is defined */
    if (Mask && (bang = strchrW(Mask, '!')))
    {
        if (bang == Mask) return FALSE;
        Mask = bang + 1;
    }

    symt_enum_module(&pair, Mask ? Mask : starW, se);

    return TRUE;
}