#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  void app ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_6__ {void* apps; int /*<<< orphan*/  net_client_list; int /*<<< orphan*/  root_window; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 void* AddApp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DelApp (void*) ; 
 int /*<<< orphan*/  XA_WINDOW ; 
 int /*<<< orphan*/  cmpapp ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdelete (void*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdestroy (void*,int /*<<< orphan*/  (*) (void*)) ; 
 void** tfind (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 void** tsearch (void*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_get_property_value (int /*<<< orphan*/ *) ; 
 int xcb_get_property_value_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void UpdateApps (services_discovery_t *sd)
{
    services_discovery_sys_t *p_sys = sd->p_sys;
    xcb_connection_t *conn = p_sys->conn;

    xcb_get_property_reply_t *r =
        xcb_get_property_reply (conn,
            xcb_get_property (conn, false, p_sys->root_window,
                              p_sys->net_client_list, XA_WINDOW, 0, 1024),
            NULL);
    if (r == NULL)
        return; /* FIXME: remove all entries */

    xcb_window_t *ent = xcb_get_property_value (r);
    int n = xcb_get_property_value_length (r) / 4;
    void *newnodes = NULL, *oldnodes = p_sys->apps;

    for (int i = 0; i < n; i++)
    {
        xcb_window_t id = *(ent++);
        struct app *app;

        void **pa = tfind (&id, &oldnodes, cmpapp);
        if (pa != NULL) /* existing entry */
        {
            app = *pa;
            tdelete (app, &oldnodes, cmpapp);
        }
        else /* new entry */
        {
            app = AddApp (sd, id);
            if (app == NULL)
                continue;
        }

        pa = tsearch (app, &newnodes, cmpapp);
        if (pa == NULL /* OOM */ || *pa != app /* buggy window manager */)
            DelApp (app);
    }
    free (r);

    /* Remove old nodes */
    tdestroy (oldnodes, DelApp);
    p_sys->apps = newnodes;
}