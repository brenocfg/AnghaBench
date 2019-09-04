#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ peek_len; int /*<<< orphan*/  socket; int /*<<< orphan*/ * peek_msg; int /*<<< orphan*/ * peek_msg_mem; scalar_t__ secure; } ;
typedef  TYPE_1__ netconn_t ;
typedef  size_t SIZE_T ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MSG_WAITALL ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int min (size_t,scalar_t__) ; 
 scalar_t__ read_ssl_chunk (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_get_error (int /*<<< orphan*/ ) ; 
 int sock_recv (int /*<<< orphan*/ ,void*,size_t,int) ; 

BOOL netconn_recv( netconn_t *conn, void *buf, size_t len, int flags, int *recvd )
{
    *recvd = 0;
    if (!len) return TRUE;

    if (conn->secure)
    {
        SIZE_T size, cread;
        BOOL res, eof;

        if (conn->peek_msg)
        {
            *recvd = min( len, conn->peek_len );
            memcpy( buf, conn->peek_msg, *recvd );
            conn->peek_len -= *recvd;
            conn->peek_msg += *recvd;

            if (conn->peek_len == 0)
            {
                heap_free( conn->peek_msg_mem );
                conn->peek_msg_mem = NULL;
                conn->peek_msg = NULL;
            }
            /* check if we have enough data from the peek buffer */
            if (!(flags & MSG_WAITALL) || *recvd == len) return TRUE;
        }
        size = *recvd;

        do {
            res = read_ssl_chunk(conn, (BYTE*)buf+size, len-size, &cread, &eof);
            if(!res) {
                WARN("read_ssl_chunk failed\n");
                if(!size)
                    return FALSE;
                break;
            }

            if(eof) {
                TRACE("EOF\n");
                break;
            }

            size += cread;
        }while(!size || ((flags & MSG_WAITALL) && size < len));

        TRACE("received %ld bytes\n", size);
        *recvd = size;
        return TRUE;
    }
    if ((*recvd = sock_recv( conn->socket, buf, len, flags )) == -1)
    {
        set_last_error( sock_get_error( errno ) );
        return FALSE;
    }
    return TRUE;
}