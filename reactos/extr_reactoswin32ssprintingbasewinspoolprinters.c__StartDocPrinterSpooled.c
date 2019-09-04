#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  JobId; int /*<<< orphan*/  Path; } ;
struct TYPE_12__ {int /*<<< orphan*/  pDocName; scalar_t__ pDatatype; } ;
struct TYPE_11__ {int /*<<< orphan*/  pDocument; scalar_t__ pDatatype; } ;
struct TYPE_10__ {scalar_t__ hSPLFile; int /*<<< orphan*/  dwJobID; } ;
typedef  TYPE_1__* PSPOOLER_HANDLE ;
typedef  TYPE_2__* PJOB_INFO_1W ;
typedef  TYPE_3__* PDOC_INFO_1W ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  TYPE_4__* PADDJOB_INFO_1W ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetJobW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetJobW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hProcessHeap ; 

__attribute__((used)) static DWORD
_StartDocPrinterSpooled(PSPOOLER_HANDLE pHandle, PDOC_INFO_1W pDocInfo1, PADDJOB_INFO_1W pAddJobInfo1)
{
    DWORD cbNeeded;
    DWORD dwErrorCode;
    PJOB_INFO_1W pJobInfo1 = NULL;

    // Create the spool file.
    pHandle->hSPLFile = CreateFileW(pAddJobInfo1->Path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
    if (pHandle->hSPLFile == INVALID_HANDLE_VALUE)
    {
        dwErrorCode = GetLastError();
        ERR("CreateFileW failed for \"%S\" with error %lu!\n", pAddJobInfo1->Path, dwErrorCode);
        goto Cleanup;
    }

    // Get the size of the job information.
    GetJobW((HANDLE)pHandle, pAddJobInfo1->JobId, 1, NULL, 0, &cbNeeded);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        dwErrorCode = GetLastError();
        ERR("GetJobW failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // Allocate enough memory for the returned job information.
    pJobInfo1 = HeapAlloc(hProcessHeap, 0, cbNeeded);
    if (!pJobInfo1)
    {
        dwErrorCode = ERROR_NOT_ENOUGH_MEMORY;
        ERR("HeapAlloc failed!\n");
        goto Cleanup;
    }

    // Get the job information.
    if (!GetJobW((HANDLE)pHandle, pAddJobInfo1->JobId, 1, (PBYTE)pJobInfo1, cbNeeded, &cbNeeded))
    {
        dwErrorCode = GetLastError();
        ERR("GetJobW failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // Add our document information.
    if (pDocInfo1->pDatatype)
        pJobInfo1->pDatatype = pDocInfo1->pDatatype;

    pJobInfo1->pDocument = pDocInfo1->pDocName;

    // Set the new job information.
    if (!SetJobW((HANDLE)pHandle, pAddJobInfo1->JobId, 1, (PBYTE)pJobInfo1, 0))
    {
        dwErrorCode = GetLastError();
        ERR("SetJobW failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // We were successful!
    pHandle->dwJobID = pAddJobInfo1->JobId;
    dwErrorCode = ERROR_SUCCESS;

Cleanup:
    if (pJobInfo1)
        HeapFree(hProcessHeap, 0, pJobInfo1);

    return dwErrorCode;
}