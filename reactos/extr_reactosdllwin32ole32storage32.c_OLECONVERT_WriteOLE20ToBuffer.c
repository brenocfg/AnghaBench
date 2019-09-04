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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPSTORAGE ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IStorage_CopyTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static DWORD OLECONVERT_WriteOLE20ToBuffer(LPSTORAGE pStorage, BYTE **pData)
{
    HANDLE hFile;
    HRESULT hRes;
    DWORD nDataLength = 0;
    IStorage *pTempStorage;
    WCHAR wstrTempDir[MAX_PATH], wstrTempFile[MAX_PATH];
    static const WCHAR wstrPrefix[] = {'s', 'i', 's', 0};

    *pData = NULL;

    /* Create temp Storage */
    GetTempPathW(MAX_PATH, wstrTempDir);
    GetTempFileNameW(wstrTempDir, wstrPrefix, 0, wstrTempFile);
    hRes = StgCreateDocfile(wstrTempFile, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &pTempStorage);

    if(hRes == S_OK)
    {
        /* Copy Src Storage to the Temp Storage */
        IStorage_CopyTo(pStorage, 0, NULL, NULL, pTempStorage);
        IStorage_Release(pTempStorage);

        /* Open Temp Storage as a file and copy to memory */
        hFile = CreateFileW(wstrTempFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if(hFile != INVALID_HANDLE_VALUE)
        {
            nDataLength = GetFileSize(hFile, NULL);
            *pData = HeapAlloc(GetProcessHeap(),0,nDataLength);
            ReadFile(hFile, *pData, nDataLength, &nDataLength, 0);
            CloseHandle(hFile);
        }
        DeleteFileW(wstrTempFile);
    }
    return nDataLength;
}