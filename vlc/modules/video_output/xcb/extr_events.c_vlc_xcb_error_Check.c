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
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
struct TYPE_4__ {int error_code; } ;
typedef  TYPE_1__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  vout_display_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,int) ; 
 TYPE_1__* xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int vlc_xcb_error_Check(vout_display_t *vd, xcb_connection_t *conn,
                        const char *str, xcb_void_cookie_t ck)
{
    xcb_generic_error_t *err;

    err = xcb_request_check (conn, ck);
    if (err)
    {
        int code = err->error_code;

        free (err);
        msg_Err (vd, "%s: X11 error %d", str, code);
        assert (code != 0);
        return code;
    }
    return 0;
}