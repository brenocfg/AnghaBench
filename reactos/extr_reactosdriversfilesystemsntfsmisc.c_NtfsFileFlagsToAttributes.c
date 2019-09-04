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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int* PULONG ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int NTFS_FILE_TYPE_DIRECTORY ; 

VOID
NtfsFileFlagsToAttributes(ULONG NtfsAttributes,
                          PULONG FileAttributes)
{
    *FileAttributes = NtfsAttributes;
    if ((NtfsAttributes & NTFS_FILE_TYPE_DIRECTORY) == NTFS_FILE_TYPE_DIRECTORY)
    {
        *FileAttributes = NtfsAttributes & ~NTFS_FILE_TYPE_DIRECTORY;
        *FileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
    }

    if (NtfsAttributes == 0)
        *FileAttributes = FILE_ATTRIBUTE_NORMAL;
}