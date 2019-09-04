#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pool {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ModuleName; int /*<<< orphan*/  SymType; } ;
struct module {TYPE_4__ module; int /*<<< orphan*/  reloc_delta; TYPE_3__** format_info; } ;
struct image_section_map {int dummy; } ;
struct image_file_map {int dummy; } ;
struct hash_table {int dummy; } ;
struct elf_thunk_area {char* member_0; int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_6__ {TYPE_1__* elf_info; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  elf_addr; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t DFI_ELF ; 
 int FALSE ; 
 char const* IMAGE_NO_MAP ; 
 int /*<<< orphan*/  SHT_NULL ; 
 int SYMOPT_PUBLICS_ONLY ; 
 int /*<<< orphan*/  S_ElfW ; 
 int /*<<< orphan*/  S_WineLoaderW ; 
 int /*<<< orphan*/  SymExport ; 
 int THUNK_ORDINAL_LOAD ; 
 int THUNK_ORDINAL_NOTYPE ; 
 int TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int dbghelp_options ; 
 int dwarf2_parse (struct module*,int /*<<< orphan*/ ,struct elf_thunk_area*,struct image_file_map*) ; 
 int elf_check_alternate (struct image_file_map*,struct module*) ; 
 scalar_t__ elf_find_section (struct image_file_map*,char*,int /*<<< orphan*/ ,struct image_section_map*) ; 
 int /*<<< orphan*/  elf_finish_stabs_info (struct module*,struct hash_table*) ; 
 int /*<<< orphan*/  elf_hash_symtab (struct module*,struct pool*,struct hash_table*,struct image_file_map*,struct elf_thunk_area*) ; 
 scalar_t__ elf_new_public_symbols (struct module*,struct hash_table*) ; 
 int /*<<< orphan*/  elf_new_wine_thunks (struct module*,struct hash_table*,struct elf_thunk_area*) ; 
 int /*<<< orphan*/  image_get_map_size (struct image_section_map*) ; 
 char* image_map_section (struct image_section_map*) ; 
 int /*<<< orphan*/  image_unmap_section (struct image_section_map*) ; 
 int stabs_parse (struct module*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strstrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL elf_load_debug_info_from_map(struct module* module,
                                         struct image_file_map* fmap,
                                         struct pool* pool,
                                         struct hash_table* ht_symtab)
{
    BOOL                ret = FALSE, lret;
    struct elf_thunk_area thunks[] = 
    {
        {"__wine_spec_import_thunks",           THUNK_ORDINAL_NOTYPE, 0, 0},    /* inter DLL calls */
        {"__wine_spec_delayed_import_loaders",  THUNK_ORDINAL_LOAD,   0, 0},    /* delayed inter DLL calls */
        {"__wine_spec_delayed_import_thunks",   THUNK_ORDINAL_LOAD,   0, 0},    /* delayed inter DLL calls */
        {"__wine_delay_load",                   THUNK_ORDINAL_LOAD,   0, 0},    /* delayed inter DLL calls */
        {"__wine_spec_thunk_text_16",           -16,                  0, 0},    /* 16 => 32 thunks */
        {"__wine_spec_thunk_text_32",           -32,                  0, 0},    /* 32 => 16 thunks */
        {NULL,                                  0,                    0, 0}
    };

    module->module.SymType = SymExport;

    /* create a hash table for the symtab */
    elf_hash_symtab(module, pool, ht_symtab, fmap, thunks);

    if (!(dbghelp_options & SYMOPT_PUBLICS_ONLY))
    {
        struct image_section_map stab_sect, stabstr_sect;

        /* check if we need an alternate file (from debuglink or build-id) */
        ret = elf_check_alternate(fmap, module);

        if (elf_find_section(fmap, ".stab", SHT_NULL, &stab_sect) &&
            elf_find_section(fmap, ".stabstr", SHT_NULL, &stabstr_sect))
        {
            const char* stab;
            const char* stabstr;

            stab = image_map_section(&stab_sect);
            stabstr = image_map_section(&stabstr_sect);
            if (stab != IMAGE_NO_MAP && stabstr != IMAGE_NO_MAP)
            {
                /* OK, now just parse all of the stabs. */
                lret = stabs_parse(module, module->format_info[DFI_ELF]->u.elf_info->elf_addr,
                                   stab, image_get_map_size(&stab_sect),
                                   stabstr, image_get_map_size(&stabstr_sect),
                                   NULL, NULL);
                if (lret)
                    /* and fill in the missing information for stabs */
                    elf_finish_stabs_info(module, ht_symtab);
                else
                    WARN("Couldn't correctly read stabs\n");
                ret = ret || lret;
            }
            image_unmap_section(&stab_sect);
            image_unmap_section(&stabstr_sect);
        }
        lret = dwarf2_parse(module, module->reloc_delta, thunks, fmap);
        ret = ret || lret;
    }
    if (strstrW(module->module.ModuleName, S_ElfW) ||
        !strcmpW(module->module.ModuleName, S_WineLoaderW))
    {
        /* add the thunks for native libraries */
        if (!(dbghelp_options & SYMOPT_PUBLICS_ONLY))
            elf_new_wine_thunks(module, ht_symtab, thunks);
    }
    /* add all the public symbols from symtab */
    if (elf_new_public_symbols(module, ht_symtab) && !ret) ret = TRUE;

    return ret;
}