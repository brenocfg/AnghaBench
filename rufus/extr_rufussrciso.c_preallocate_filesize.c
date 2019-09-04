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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  file_length ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FileAllocationInfo ; 
 int /*<<< orphan*/  FileEndOfFileInfo ; 
 int /*<<< orphan*/  SetFileInformationByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __inline preallocate_filesize(HANDLE hFile, int64_t file_length)
{
	SetFileInformationByHandle(hFile, FileEndOfFileInfo, &file_length, sizeof(file_length));

	// FileAllocationInfo does not require the size to be a multiple of the cluster size; the FS driver takes care of this.
	SetFileInformationByHandle(hFile, FileAllocationInfo, &file_length, sizeof(file_length));
}