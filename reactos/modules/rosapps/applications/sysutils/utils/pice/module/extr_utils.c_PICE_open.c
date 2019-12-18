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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_NO_INTERMEDIATE_BUFFERING ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int OF_READ ; 
 int OF_READWRITE ; 
 int OF_SHARE_COMPAT ; 
 int OF_SHARE_DENY_NONE ; 
 int OF_SHARE_DENY_READ ; 
 int OF_SHARE_DENY_WRITE ; 
 int OF_SHARE_EXCLUSIVE ; 
 int OF_WRITE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HANDLE PICE_open (LPCWSTR	lpPathName,	int	iReadWrite)
{
	DWORD dwAccessMask = 0;
	DWORD dwShareMode = 0;
	UNICODE_STRING TmpFileName;
	OBJECT_ATTRIBUTES ObjectAttributes;
	IO_STATUS_BLOCK StatusBlock;
	HANDLE hfile;
	NTSTATUS status;


	DPRINT((0,"PICE_open: %S\n", lpPathName));

	if ( (iReadWrite & OF_READWRITE ) == OF_READWRITE )
		dwAccessMask = GENERIC_READ | GENERIC_WRITE;
	else if ( (iReadWrite & OF_READ ) == OF_READ )
		dwAccessMask = GENERIC_READ;
	else if ( (iReadWrite & OF_WRITE ) == OF_WRITE )
		dwAccessMask = GENERIC_WRITE;

	if ((iReadWrite & OF_SHARE_COMPAT) == OF_SHARE_COMPAT )
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE;
	else if ((iReadWrite & OF_SHARE_DENY_NONE) == OF_SHARE_DENY_NONE)
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE;
	else if ((iReadWrite & OF_SHARE_DENY_READ) == OF_SHARE_DENY_READ)
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_DELETE;
	else if ((iReadWrite & OF_SHARE_DENY_WRITE) == OF_SHARE_DENY_WRITE )
		dwShareMode = FILE_SHARE_READ | FILE_SHARE_DELETE;
	else if ((iReadWrite & OF_SHARE_EXCLUSIVE) == OF_SHARE_EXCLUSIVE)
		dwShareMode = 0;

	RtlInitUnicodeString (&TmpFileName, lpPathName);
  	InitializeObjectAttributes(&ObjectAttributes,
                             &TmpFileName,
                             0,
                             NULL,
                             NULL);

	status = NtOpenFile( &hfile,
                      dwAccessMask,
                      &ObjectAttributes,
                      &StatusBlock, dwShareMode, FILE_NO_INTERMEDIATE_BUFFERING);
	//BUG BUG check status!!!
	if( !NT_SUCCESS( status ) ){
		DPRINT((0,"PICE_open: NtOpenFile error: %x\n", status));
		return 0;
	}
	return hfile;
}