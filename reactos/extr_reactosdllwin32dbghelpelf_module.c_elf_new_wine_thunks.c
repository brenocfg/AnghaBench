#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct symtab_elt {TYPE_2__* symp; TYPE_1__ ht_elt; int /*<<< orphan*/  compiland; scalar_t__ used; } ;
struct symt_ht {int /*<<< orphan*/  symt; } ;
struct module {scalar_t__ reloc_delta; int sortlist_valid; } ;
struct location {scalar_t__ offset; int /*<<< orphan*/  reg; int /*<<< orphan*/  kind; } ;
struct hash_table_iter {int dummy; } ;
struct hash_table {int dummy; } ;
struct elf_thunk_area {int /*<<< orphan*/  ordinal; } ;
typedef  scalar_t__ ULONG64 ;
struct TYPE_4__ {scalar_t__ st_value; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_info; } ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  ELF32_ST_BIND (int /*<<< orphan*/ ) ; 
 int ELF32_ST_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  STB_LOCAL ; 
#define  STT_FUNC 129 
#define  STT_OBJECT 128 
 int TRUE ; 
 int elf_is_in_thunk_area (scalar_t__,struct elf_thunk_area const*) ; 
 int /*<<< orphan*/  hash_table_iter_init (struct hash_table const*,struct hash_table_iter*,int /*<<< orphan*/ *) ; 
 struct symtab_elt* hash_table_iter_up (struct hash_table_iter*) ; 
 int /*<<< orphan*/  loc_absolute ; 
 struct symt_ht* symt_find_nearest (struct module*,scalar_t__) ; 
 int /*<<< orphan*/  symt_get_address (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  symt_new_function (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symt_new_global_variable (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct location,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symt_new_thunk (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elf_new_wine_thunks(struct module* module, const struct hash_table* ht_symtab,
                               const struct elf_thunk_area* thunks)
{
    int		                j;
    struct hash_table_iter      hti;
    struct symtab_elt*          ste;
    DWORD_PTR                   addr;
    struct symt_ht*             symt;

    hash_table_iter_init(ht_symtab, &hti, NULL);
    while ((ste = hash_table_iter_up(&hti)))
    {
        if (ste->used) continue;

        addr = module->reloc_delta + ste->symp->st_value;

        j = elf_is_in_thunk_area(ste->symp->st_value, thunks);
        if (j >= 0) /* thunk found */
        {
            symt_new_thunk(module, ste->compiland, ste->ht_elt.name, thunks[j].ordinal,
                           addr, ste->symp->st_size);
        }
        else
        {
            ULONG64     ref_addr;
            struct location loc;

            symt = symt_find_nearest(module, addr);
            if (symt && !symt_get_address(&symt->symt, &ref_addr))
                ref_addr = addr;
            if (!symt || addr != ref_addr)
            {
                /* creating public symbols for all the ELF symbols which haven't been
                 * used yet (ie we have no debug information on them)
                 * That's the case, for example, of the .spec.c files
                 */
                switch (ELF32_ST_TYPE(ste->symp->st_info))
                {
                case STT_FUNC:
                    symt_new_function(module, ste->compiland, ste->ht_elt.name,
                                      addr, ste->symp->st_size, NULL);
                    break;
                case STT_OBJECT:
                    loc.kind = loc_absolute;
                    loc.reg = 0;
                    loc.offset = addr;
                    symt_new_global_variable(module, ste->compiland, ste->ht_elt.name,
                                             ELF32_ST_BIND(ste->symp->st_info) == STB_LOCAL,
                                             loc, ste->symp->st_size, NULL);
                    break;
                default:
                    FIXME("Shouldn't happen\n");
                    break;
                }
                /* FIXME: this is a hack !!!
                 * we are adding new symbols, but as we're parsing a symbol table
                 * (hopefully without duplicate symbols) we delay rebuilding the sorted
                 * module table until we're done with the symbol table
                 * Otherwise, as we intertwine symbols' add and lookup, performance
                 * is rather bad
                 */
                module->sortlist_valid = TRUE;
            }
        }
    }
    /* see comment above */
    module->sortlist_valid = FALSE;
    return TRUE;
}