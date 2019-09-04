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
struct TYPE_5__ {int /*<<< orphan*/  toc; } ;
struct TYPE_4__ {int /*<<< orphan*/  toc; } ;
struct TYPE_6__ {TYPE_2__ ds; TYPE_1__ jg; } ;
struct pdb_file_info {int kind; TYPE_3__ u; scalar_t__ image; } ;
struct PDB_JG_HEADER {int dummy; } ;
struct PDB_DS_HEADER {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  PDB_DS 129 
#define  PDB_JG 128 
 void* pdb_read_ds_file (struct PDB_DS_HEADER const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pdb_read_jg_file (struct PDB_JG_HEADER const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* pdb_read_file(const struct pdb_file_info* pdb_file,
                           DWORD file_nr)
{
    switch (pdb_file->kind)
    {
    case PDB_JG:
        return pdb_read_jg_file((const struct PDB_JG_HEADER*)pdb_file->image,
                                pdb_file->u.jg.toc, file_nr);
    case PDB_DS:
        return pdb_read_ds_file((const struct PDB_DS_HEADER*)pdb_file->image,
                                pdb_file->u.ds.toc, file_nr);
    }
    return NULL;
}