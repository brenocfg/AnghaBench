#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
typedef  int /*<<< orphan*/  ftp_session_t ;
struct TYPE_3__ {scalar_t__ nFileSizeLow; } ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  TYPE_1__ BY_HANDLE_FILE_INFORMATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DATA_PACKET_SIZE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetFileInformationByHandle (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int sock_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int*) ; 

__attribute__((used)) static BOOL FTP_SendData(ftp_session_t *lpwfs, INT nDataSocket, HANDLE hFile)
{
    BY_HANDLE_FILE_INFORMATION fi;
    DWORD nBytesRead = 0;
    DWORD nBytesSent = 0;
    DWORD nTotalSent = 0;
    DWORD nBytesToSend, nLen;
    int nRC = 1;
    time_t s_long_time, e_long_time;
    LONG nSeconds;
    CHAR *lpszBuffer;

    TRACE("\n");
    lpszBuffer = heap_alloc_zero(sizeof(CHAR)*DATA_PACKET_SIZE);

    /* Get the size of the file. */
    GetFileInformationByHandle(hFile, &fi);
    time(&s_long_time);

    do
    {
        nBytesToSend = nBytesRead - nBytesSent;

        if (nBytesToSend <= 0)
        {
            /* Read data from file. */
            nBytesSent = 0;
            if (!ReadFile(hFile, lpszBuffer, DATA_PACKET_SIZE, &nBytesRead, 0))
            ERR("Failed reading from file\n");

            if (nBytesRead > 0)
                nBytesToSend = nBytesRead;
            else
                break;
        }

        nLen = DATA_PACKET_SIZE < nBytesToSend ?
            DATA_PACKET_SIZE : nBytesToSend;
        nRC  = sock_send(nDataSocket, lpszBuffer, nLen, 0);

        if (nRC != -1)
        {
            nBytesSent += nRC;
            nTotalSent += nRC;
        }

        /* Do some computation to display the status. */
        time(&e_long_time);
        nSeconds = e_long_time - s_long_time;
        if( nSeconds / 60 > 0 )
        {
            TRACE( "%d bytes of %d bytes (%d%%) in %d min %d sec estimated remaining time %d sec\n",
            nTotalSent, fi.nFileSizeLow, nTotalSent*100/fi.nFileSizeLow, nSeconds / 60,
            nSeconds % 60, (fi.nFileSizeLow - nTotalSent) * nSeconds / nTotalSent );
        }
        else
        {
            TRACE( "%d bytes of %d bytes (%d%%) in %d sec estimated remaining time %d sec\n",
            nTotalSent, fi.nFileSizeLow, nTotalSent*100/fi.nFileSizeLow, nSeconds,
            (fi.nFileSizeLow - nTotalSent) * nSeconds / nTotalSent);
        }
    } while (nRC != -1);

    TRACE("file transfer complete!\n");

    heap_free(lpszBuffer);
    return nTotalSent;
}