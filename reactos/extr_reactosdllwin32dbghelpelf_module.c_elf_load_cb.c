#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ SymType; } ;
struct module {TYPE_4__ module; TYPE_3__** format_info; } ;
struct image_file_map {int dummy; } ;
struct TYPE_16__ {void* load_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_17__ {TYPE_5__ process; } ;
struct elf_map_file_data {TYPE_6__ u; int /*<<< orphan*/  kind; } ;
struct TYPE_19__ {struct module* module; } ;
struct elf_load {scalar_t__ name; TYPE_9__ elf_info; TYPE_7__* pcs; int /*<<< orphan*/  ret; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_18__ {int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {TYPE_1__* elf_info; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
struct TYPE_12__ {int elf_mark; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t DFI_ELF ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  elf_load_file_from_fmap (TYPE_7__*,int /*<<< orphan*/  const*,struct image_file_map*,unsigned long,int /*<<< orphan*/ ,TYPE_9__*) ; 
 scalar_t__ elf_map_file (struct elf_map_file_data*,struct image_file_map*) ; 
 int /*<<< orphan*/  elf_search_and_load_file (TYPE_7__*,int /*<<< orphan*/  const*,unsigned long,unsigned long,TYPE_9__*) ; 
 int /*<<< orphan*/  from_process ; 
 int lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,scalar_t__,int) ; 
 struct module* module_is_already_loaded (TYPE_7__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strrchrW (int /*<<< orphan*/  const*,char) ; 

__attribute__((used)) static BOOL elf_load_cb(const WCHAR* name, unsigned long load_addr,
                        unsigned long dyn_addr, BOOL is_system, void* user)
{
    struct elf_load*    el = user;
    BOOL                ret = TRUE;
    const WCHAR*        p;

    if (is_system) /* virtual ELF module, created by system. handle it from memory */
    {
        struct module*                  module;
        struct elf_map_file_data        emfd;
        struct image_file_map           fmap;

        if ((module = module_is_already_loaded(el->pcs, name)))
        {
            el->elf_info.module = module;
            el->elf_info.module->format_info[DFI_ELF]->u.elf_info->elf_mark = 1;
            return module->module.SymType;
        }

        emfd.kind = from_process;
        emfd.u.process.handle = el->pcs->handle;
        emfd.u.process.load_addr = (void*)load_addr;

        if (elf_map_file(&emfd, &fmap))
            el->ret = elf_load_file_from_fmap(el->pcs, name, &fmap, load_addr, 0, &el->elf_info);
        return TRUE;
    }
    if (el->name)
    {
        /* memcmp is needed for matches when bufstr contains also version information
         * el->name: libc.so, name: libc.so.6.0
         */
        p = strrchrW(name, '/');
        if (!p++) p = name;
    }

    if (!el->name || !memcmp(p, el->name, lstrlenW(el->name) * sizeof(WCHAR)))
    {
        el->ret = elf_search_and_load_file(el->pcs, name, load_addr, dyn_addr, &el->elf_info);
        if (el->name) ret = FALSE;
    }

    return ret;
}