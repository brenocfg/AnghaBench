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
struct process {int dummy; } ;
struct module {int dummy; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int SYMOPT_PUBLICS_ONLY ; 
 int TRUE ; 
 int dbghelp_options ; 
 scalar_t__ pe_load_coff_symbol_table (struct module*) ; 
 scalar_t__ pe_load_dwarf (struct module*) ; 
 scalar_t__ pe_load_export_debug_info (struct process const*,struct module*) ; 
 scalar_t__ pe_load_msc_debug_info (struct process const*,struct module*) ; 
 scalar_t__ pe_load_rsym (struct module*) ; 
 int pe_load_stabs (struct process const*,struct module*) ; 

BOOL pe_load_debug_info(const struct process* pcs, struct module* module)
{
    BOOL                ret = FALSE;

    if (!(dbghelp_options & SYMOPT_PUBLICS_ONLY))
    {
        ret = pe_load_stabs(pcs, module);
        ret = pe_load_dwarf(module) || ret;
        #ifndef DBGHELP_STATIC_LIB
        ret = pe_load_msc_debug_info(pcs, module) || ret;
        ret = pe_load_rsym(module) || ret;
        #endif

        ret = ret || pe_load_coff_symbol_table(module); /* FIXME */
        /* if we still have no debug info (we could only get SymExport at this
         * point), then do the SymExport except if we have an ELF container,
         * in which case we'll rely on the export's on the ELF side
         */
    }
    /* FIXME shouldn't we check that? if (!module_get_debug(pcs, module)) */
    if (pe_load_export_debug_info(pcs, module) && !ret)
        ret = TRUE;

    return ret;
}