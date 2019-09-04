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
typedef  int /*<<< orphan*/  ftp_session_t ;
typedef  int /*<<< orphan*/ * LPFILEPROPERTIESW ;
typedef  int* LPDWORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  FILEPROPERTIESW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NO_MORE_FILES ; 
 scalar_t__ FALSE ; 
 scalar_t__ FTP_ParseNextFile (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERNET_SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_realloc_zero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL FTP_ParseDirectory(ftp_session_t *lpwfs, INT nSocket, LPCWSTR lpszSearchFile,
    LPFILEPROPERTIESW *lpafp, LPDWORD dwfp)
{
    BOOL bSuccess = TRUE;
    INT sizeFilePropArray = 500;/*20; */
    INT indexFilePropArray = -1;

    TRACE("\n");

    /* Allocate initial file properties array */
    *lpafp = heap_alloc_zero(sizeof(FILEPROPERTIESW)*(sizeFilePropArray));
    if (!*lpafp)
        return FALSE;

    do {
        if (indexFilePropArray+1 >= sizeFilePropArray)
        {
            LPFILEPROPERTIESW tmpafp;
            
            sizeFilePropArray *= 2;
            tmpafp = heap_realloc_zero(*lpafp, sizeof(FILEPROPERTIESW)*sizeFilePropArray);
            if (NULL == tmpafp)
            {
                bSuccess = FALSE;
                break;
            }

            *lpafp = tmpafp;
        }
        indexFilePropArray++;
    } while (FTP_ParseNextFile(nSocket, lpszSearchFile, &(*lpafp)[indexFilePropArray]));

    if (bSuccess && indexFilePropArray)
    {
        if (indexFilePropArray < sizeFilePropArray - 1)
        {
            LPFILEPROPERTIESW tmpafp;

            tmpafp = heap_realloc(*lpafp, sizeof(FILEPROPERTIESW)*indexFilePropArray);
            if (NULL != tmpafp)
                *lpafp = tmpafp;
        }
        *dwfp = indexFilePropArray;
    }
    else
    {
        heap_free(*lpafp);
        INTERNET_SetLastError(ERROR_NO_MORE_FILES);
        bSuccess = FALSE;
    }

    return bSuccess;
}