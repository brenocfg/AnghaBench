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
struct PDB_DS_TOC {size_t num_files; int* file_size; } ;
struct PDB_DS_HEADER {int block_size; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 void* pdb_ds_read (struct PDB_DS_HEADER const*,size_t const*,int) ; 

__attribute__((used)) static void* pdb_read_ds_file(const struct PDB_DS_HEADER* pdb,
                              const struct PDB_DS_TOC* toc, DWORD file_nr)
{
    const DWORD*                block_list;
    DWORD                       i;

    if (!toc || file_nr >= toc->num_files) return NULL;
    if (toc->file_size[file_nr] == 0 || toc->file_size[file_nr] == 0xFFFFFFFF) return NULL;

    block_list = &toc->file_size[toc->num_files];
    for (i = 0; i < file_nr; i++)
        block_list += (toc->file_size[i] + pdb->block_size - 1) / pdb->block_size;

    return pdb_ds_read(pdb, block_list, toc->file_size[file_nr]);
}