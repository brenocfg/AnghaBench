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
struct pdb_file_info {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  pdb_free (void*) ; 
 unsigned int pdb_get_stream_by_name (struct pdb_file_info const*,char*) ; 
 void* pdb_read_file (struct pdb_file_info const*,unsigned int) ; 

__attribute__((used)) static void* pdb_read_strings(const struct pdb_file_info* pdb_file)
{
    unsigned idx;
    void *ret;

    idx = pdb_get_stream_by_name(pdb_file, "/names");
    if (idx != -1)
    {
        ret = pdb_read_file( pdb_file, idx );
        if (ret && *(const DWORD *)ret == 0xeffeeffe) return ret;
        pdb_free( ret );
    }
    WARN("string table not found\n");
    return NULL;
}