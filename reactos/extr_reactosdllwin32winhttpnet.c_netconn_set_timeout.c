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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ netconn_t ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  sock_get_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

DWORD netconn_set_timeout( netconn_t *netconn, BOOL send, int value )
{
    struct timeval tv;

    /* value is in milliseconds, convert to struct timeval */
    tv.tv_sec = value / 1000;
    tv.tv_usec = (value % 1000) * 1000;

    if (setsockopt( netconn->socket, SOL_SOCKET, send ? SO_SNDTIMEO : SO_RCVTIMEO, (void*)&tv, sizeof(tv) ) == -1)
    {
        WARN("setsockopt failed (%s)\n", strerror( errno ));
        return sock_get_error( errno );
    }
    return ERROR_SUCCESS;
}