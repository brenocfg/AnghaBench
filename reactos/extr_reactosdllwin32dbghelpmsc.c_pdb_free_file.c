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
struct TYPE_5__ {int /*<<< orphan*/ * toc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * toc; } ;
struct TYPE_6__ {TYPE_2__ ds; TYPE_1__ jg; } ;
struct pdb_file_info {int kind; int /*<<< orphan*/  stream_dict; TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PDB_DS 129 
#define  PDB_JG 128 
 int /*<<< orphan*/  pdb_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdb_free_file(struct pdb_file_info* pdb_file)
{
    switch (pdb_file->kind)
    {
    case PDB_JG:
        pdb_free(pdb_file->u.jg.toc);
        pdb_file->u.jg.toc = NULL;
        break;
    case PDB_DS:
        pdb_free(pdb_file->u.ds.toc);
        pdb_file->u.ds.toc = NULL;
        break;
    }
    HeapFree(GetProcessHeap(), 0, pdb_file->stream_dict);
}