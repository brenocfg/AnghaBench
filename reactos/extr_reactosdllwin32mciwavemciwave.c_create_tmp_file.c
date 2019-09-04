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
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ HMMIO ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTempFileNameW (char*,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MCIERR_FILE_NOT_FOUND ; 
 int MMIO_ALLOCBUF ; 
 int MMIO_CREATE ; 
 int MMIO_READWRITE ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 scalar_t__ mmioOpenW (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static DWORD create_tmp_file(HMMIO* hFile, LPWSTR* pszTmpFileName)
{
    WCHAR       szTmpPath[MAX_PATH];
    WCHAR       szPrefix[4];
    DWORD       dwRet = MMSYSERR_NOERROR;

    szPrefix[0] = 'M';
    szPrefix[1] = 'C';
    szPrefix[2] = 'I';
    szPrefix[3] = '\0';

    if (!GetTempPathW(ARRAY_SIZE(szTmpPath), szTmpPath)) {
        WARN("can't retrieve temp path!\n");
        *pszTmpFileName = NULL;
        return MCIERR_FILE_NOT_FOUND;
    }

    *pszTmpFileName = HeapAlloc(GetProcessHeap(),
                                HEAP_ZERO_MEMORY,
                                MAX_PATH * sizeof(WCHAR));
    if (!GetTempFileNameW(szTmpPath, szPrefix, 0, *pszTmpFileName)) {
        WARN("can't retrieve temp file name!\n");
        HeapFree(GetProcessHeap(), 0, *pszTmpFileName);
        return MCIERR_FILE_NOT_FOUND;
    }

    TRACE("%s!\n", debugstr_w(*pszTmpFileName));

    if (*pszTmpFileName && (*pszTmpFileName)[0]) {

        *hFile = mmioOpenW(*pszTmpFileName, NULL,
                           MMIO_ALLOCBUF | MMIO_READWRITE | MMIO_CREATE);

        if (*hFile == 0) {
            WARN("can't create file=%s!\n", debugstr_w(*pszTmpFileName));
            /* temporary file could not be created. clean filename. */
            HeapFree(GetProcessHeap(), 0, *pszTmpFileName);
            dwRet = MCIERR_FILE_NOT_FOUND;
        }
    }
    return dwRet;
}