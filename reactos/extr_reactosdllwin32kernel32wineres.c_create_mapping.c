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
struct mapping_info {scalar_t__ file; int /*<<< orphan*/  size; scalar_t__ read_write; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct mapping_info* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  destroy_mapping (struct mapping_info*) ; 
 scalar_t__ map_file_into_memory (struct mapping_info*) ; 

__attribute__((used)) static struct mapping_info *create_mapping( LPCWSTR name, BOOL rw )
{
    struct mapping_info *mi;

    mi = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof *mi );
    if (!mi)
        return NULL;

    mi->read_write = rw;

    mi->file = CreateFileW( name, GENERIC_READ | (rw ? GENERIC_WRITE : 0),
                            0, NULL, OPEN_EXISTING, 0, 0 );

    if (mi->file != INVALID_HANDLE_VALUE)
    {
        mi->size = GetFileSize( mi->file, NULL );

        if (map_file_into_memory( mi ))
            return mi;
    }
    destroy_mapping( mi );
    return NULL;
}