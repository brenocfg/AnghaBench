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
typedef  int /*<<< orphan*/  xcb_shm_query_version_reply_t ;
typedef  int /*<<< orphan*/  xcb_shm_query_version_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_shm_query_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_shm_query_version_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool CheckSHM (xcb_connection_t *conn)
{
#ifdef HAVE_SYS_SHM_H
    xcb_shm_query_version_cookie_t ck = xcb_shm_query_version (conn);
    xcb_shm_query_version_reply_t *r;

    r = xcb_shm_query_version_reply (conn, ck, NULL);
    free (r);
    return r != NULL;
#else
    (void) conn;
    return false;
#endif
}