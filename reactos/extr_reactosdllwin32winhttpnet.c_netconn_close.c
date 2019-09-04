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
struct TYPE_4__ {int /*<<< orphan*/  host; int /*<<< orphan*/  socket; int /*<<< orphan*/  ssl_ctx; struct TYPE_4__* extra_buf; struct TYPE_4__* ssl_buf; struct TYPE_4__* peek_msg_mem; scalar_t__ secure; } ;
typedef  TYPE_1__ netconn_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_get_error (int /*<<< orphan*/ ) ; 

BOOL netconn_close( netconn_t *conn )
{
    int res;

    if (conn->secure)
    {
        heap_free( conn->peek_msg_mem );
        heap_free(conn->ssl_buf);
        heap_free(conn->extra_buf);
        DeleteSecurityContext(&conn->ssl_ctx);
    }
    res = closesocket( conn->socket );
    release_host( conn->host );
    heap_free(conn);
    if (res == -1)
    {
        set_last_error( sock_get_error( errno ) );
        return FALSE;
    }
    return TRUE;
}