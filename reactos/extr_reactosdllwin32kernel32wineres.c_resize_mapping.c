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
struct mapping_info {int /*<<< orphan*/  size; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  SetEndOfFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_file_into_memory (struct mapping_info*) ; 
 int /*<<< orphan*/  unmap_file_from_memory (struct mapping_info*) ; 

__attribute__((used)) static BOOL resize_mapping( struct mapping_info *mi, DWORD new_size )
{
    if (!unmap_file_from_memory( mi ))
        return FALSE;

    /* change the file size */
    SetFilePointer( mi->file, new_size, NULL, FILE_BEGIN );
    if (!SetEndOfFile( mi->file ))
    {
        ERR("failed to set file size to %08x\n", new_size );
        return FALSE;
    }

    mi->size = new_size;

    return map_file_into_memory( mi );
}