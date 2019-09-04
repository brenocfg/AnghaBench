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
struct process {int /*<<< orphan*/  dbg_hdr_addr; } ;
struct elf_info {int flags; int /*<<< orphan*/  dbg_hdr_addr; TYPE_4__* module; } ;
struct TYPE_8__ {TYPE_3__** format_info; } ;
struct TYPE_6__ {TYPE_1__* elf_info; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_5__ {int elf_loader; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t DFI_ELF ; 
 int ELF_INFO_DEBUG_HEADER ; 
 int ELF_INFO_MODULE ; 
 int FALSE ; 
 int /*<<< orphan*/  S_WineLoaderW ; 
 int /*<<< orphan*/  elf_search_loader (struct process*,struct elf_info*) ; 
 int /*<<< orphan*/  module_set_module (TYPE_4__*,int /*<<< orphan*/ ) ; 

BOOL elf_read_wine_loader_dbg_info(struct process* pcs)
{
    struct elf_info     elf_info;

    elf_info.flags = ELF_INFO_DEBUG_HEADER | ELF_INFO_MODULE;
    if (!elf_search_loader(pcs, &elf_info)) return FALSE;
    elf_info.module->format_info[DFI_ELF]->u.elf_info->elf_loader = 1;
    module_set_module(elf_info.module, S_WineLoaderW);
    return (pcs->dbg_hdr_addr = elf_info.dbg_hdr_addr) != 0;
}