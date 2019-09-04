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
typedef  int INT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int DATA_PACKET_SIZE ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int FALSE ; 
 int /*<<< orphan*/  INTERNET_SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int sock_recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL FTP_RetrieveFileData(ftp_session_t *lpwfs, INT nDataSocket, HANDLE hFile)
{
    DWORD nBytesWritten;
    INT nRC = 0;
    CHAR *lpszBuffer;

    TRACE("\n");

    lpszBuffer = heap_alloc_zero(sizeof(CHAR)*DATA_PACKET_SIZE);
    if (NULL == lpszBuffer)
    {
        INTERNET_SetLastError(ERROR_OUTOFMEMORY);
        return FALSE;
    }

    while (nRC != -1)
    {
        nRC = sock_recv(nDataSocket, lpszBuffer, DATA_PACKET_SIZE, 0);
        if (nRC != -1)
        {
            /* other side closed socket. */
            if (nRC == 0)
                goto recv_end;
            WriteFile(hFile, lpszBuffer, nRC, &nBytesWritten, NULL);
        }
    }

    TRACE("Data transfer complete\n");

recv_end:
    heap_free(lpszBuffer);
    return (nRC != -1);
}