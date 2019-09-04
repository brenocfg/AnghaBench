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
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/ * PFILENAME_ATTRIBUTE ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/ * GetFileNameFromRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTFS_FILE_NAME_DOS ; 
 int /*<<< orphan*/  NTFS_FILE_NAME_POSIX ; 
 int /*<<< orphan*/  NTFS_FILE_NAME_WIN32 ; 

PFILENAME_ATTRIBUTE
GetBestFileNameFromRecord(PDEVICE_EXTENSION Vcb,
                          PFILE_RECORD_HEADER FileRecord)
{
    PFILENAME_ATTRIBUTE FileName;

    FileName = GetFileNameFromRecord(Vcb, FileRecord, NTFS_FILE_NAME_POSIX);
    if (FileName == NULL)
    {
        FileName = GetFileNameFromRecord(Vcb, FileRecord, NTFS_FILE_NAME_WIN32);
        if (FileName == NULL)
        {
            FileName = GetFileNameFromRecord(Vcb, FileRecord, NTFS_FILE_NAME_DOS);
        }
    }

    return FileName;
}