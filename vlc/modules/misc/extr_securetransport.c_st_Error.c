#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ vlc_tls_st_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  errSSLClosedAbort 130 
#define  errSSLClosedGraceful 129 
#define  errSSLWouldBlock 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int st_Error (vlc_tls_t *obj, int val)
{
    vlc_tls_st_t *sys = (vlc_tls_st_t *)obj;

    switch (val)
    {
        case errSSLWouldBlock:
            errno = EAGAIN;
            break;

        case errSSLClosedGraceful:
        case errSSLClosedAbort:
            msg_Dbg(sys->obj, "Connection closed with code %d", val);
            errno = ECONNRESET;
            break;
        default:
            msg_Err(sys->obj, "Found error %d", val);
            errno = ECONNRESET;
    }
    return -1;
}