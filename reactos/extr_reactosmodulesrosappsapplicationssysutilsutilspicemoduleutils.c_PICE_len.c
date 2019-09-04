#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ EndOfFile; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_3__ FILE_STANDARD_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileStandardInformation ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwQueryInformationFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

size_t PICE_len( HANDLE hFile )
{
	FILE_STANDARD_INFORMATION fs;
	IO_STATUS_BLOCK  iosb;
	NTSTATUS status;

  	status = ZwQueryInformationFile( hFile, &iosb, &fs, sizeof fs, FileStandardInformation );
	if( !NT_SUCCESS( status ) ){
		DPRINT((0,"PICE_len: ZwQueryInformationFile error: %x\n", status));
		return 0;
	}
	//ASSERT(fs.EndOfFile.u.HighPart == 0);
	return (size_t)fs.EndOfFile.u.LowPart;
}