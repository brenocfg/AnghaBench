#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pool {int dummy; } ;
struct TYPE_6__ {TYPE_2__* elf_info; } ;
struct module_format {TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  LoadedImageName; } ;
struct module {scalar_t__ type; TYPE_1__ module; struct module_format** format_info; } ;
struct hash_table {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  file_map; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_ELF ; 
 scalar_t__ DMT_ELF ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_load_debug_info_from_map (struct module*,int /*<<< orphan*/ *,struct pool*,struct hash_table*) ; 
 int /*<<< orphan*/  hash_table_init (struct pool*,struct hash_table*,int) ; 
 int /*<<< orphan*/  pool_destroy (struct pool*) ; 
 int /*<<< orphan*/  pool_init (struct pool*,int) ; 

BOOL elf_load_debug_info(struct module* module)
{
    BOOL                        ret = TRUE;
    struct pool                 pool;
    struct hash_table           ht_symtab;
    struct module_format*       modfmt;

    if (module->type != DMT_ELF || !(modfmt = module->format_info[DFI_ELF]) || !modfmt->u.elf_info)
    {
	ERR("Bad elf module '%s'\n", debugstr_w(module->module.LoadedImageName));
	return FALSE;
    }

    pool_init(&pool, 65536);
    hash_table_init(&pool, &ht_symtab, 256);

    ret = elf_load_debug_info_from_map(module, &modfmt->u.elf_info->file_map, &pool, &ht_symtab);

    pool_destroy(&pool);
    return ret;
}