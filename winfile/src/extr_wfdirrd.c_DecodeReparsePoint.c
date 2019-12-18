#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {int SubstituteNameLength; char* PathBuffer; int SubstituteNameOffset; } ;
struct TYPE_6__ {int ReparseTag; TYPE_1__ SymbolicLinkReparseBuffer; } ;
typedef  TYPE_2__ REPARSE_DATA_BUFFER ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppendToPath (char*,char*) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int*,int /*<<< orphan*/ *) ; 
 int FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_FLAG_OPEN_REPARSE_POINT ; 
 int /*<<< orphan*/  FILE_READ_EA ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FSCTL_GET_REPARSE_POINT ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IO_REPARSE_TAG_MOUNT_POINT ; 
 int IO_REPARSE_TAG_RESERVED_ZERO ; 
 scalar_t__ IO_REPARSE_TAG_SYMLINK ; 
 scalar_t__ IsReparseTagMicrosoft (int) ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int MAXIMUM_REPARSE_DATA_BUFFER_SIZE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  StripFilespec (char*) ; 
 int /*<<< orphan*/  lstrcpy (char*,char*) ; 
 int /*<<< orphan*/  wcsncpy_s (char*,int,char*,int) ; 

DWORD DecodeReparsePoint(LPCWSTR szMyFile, LPCWSTR szChild, LPWSTR szDest, DWORD cwcDest)
{
	HANDLE hFile;
	DWORD dwBufSize = MAXIMUM_REPARSE_DATA_BUFFER_SIZE;
	REPARSE_DATA_BUFFER* rdata;
	DWORD dwRPLen, cwcLink = 0;
	DWORD reparseTag;
	BOOL bRP;
	WCHAR szFullPath[2*MAXPATHLEN];

	lstrcpy(szFullPath, szMyFile);
	StripFilespec(szFullPath);

	if (szChild != NULL)
		AppendToPath(szFullPath, szChild);

	hFile = CreateFile(szFullPath, FILE_READ_EA, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return IO_REPARSE_TAG_RESERVED_ZERO;
		
	// Allocate the reparse data structure
	rdata = (REPARSE_DATA_BUFFER*)LocalAlloc(LMEM_FIXED, dwBufSize);
	
	// Query the reparse data
	bRP = DeviceIoControl(hFile, FSCTL_GET_REPARSE_POINT, NULL, 0, rdata, dwBufSize, &dwRPLen, NULL);

	CloseHandle(hFile);

	if (!bRP)
	{
		LocalFree(rdata);
		return IO_REPARSE_TAG_RESERVED_ZERO;
	}

	reparseTag = rdata->ReparseTag;

	if (IsReparseTagMicrosoft(rdata->ReparseTag) && 
		(rdata->ReparseTag == IO_REPARSE_TAG_MOUNT_POINT || rdata->ReparseTag == IO_REPARSE_TAG_SYMLINK)
		)		
	{
		cwcLink = rdata->SymbolicLinkReparseBuffer.SubstituteNameLength / sizeof(WCHAR);
        // NOTE: cwcLink does not include any '\0' termination character
		if (cwcLink < cwcDest)
		{
			LPWSTR szT = &rdata->SymbolicLinkReparseBuffer.PathBuffer[rdata->SymbolicLinkReparseBuffer.SubstituteNameOffset / sizeof(WCHAR)];
			if (szT[0] == '?' && szT[1] == '\\')
			{
				szT += 2;
				cwcLink -= 2;
			}
			wcsncpy_s(szDest, MAXPATHLEN, szT, cwcLink);
			szDest[cwcLink] = 0;
		}
		else
		{
			lstrcpy(szDest, L"<symbol link reference too long>");
		}
	}

	LocalFree(rdata);
	return reparseTag;
}