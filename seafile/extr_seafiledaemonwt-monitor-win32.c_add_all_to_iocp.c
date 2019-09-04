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
typedef  int /*<<< orphan*/ * gpointer ;
struct TYPE_6__ {scalar_t__* cmd_pipe; TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle_hash; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_handle_to_iocp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  seaf_debug (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,...) ; 

__attribute__((used)) static BOOL
add_all_to_iocp (SeafWTMonitor *monitor)
{
    SeafWTMonitorPriv *priv = monitor->priv;

    if (!add_handle_to_iocp(monitor, (HANDLE)monitor->cmd_pipe[0])) {

        seaf_warning("Failed to add cmd_pipe to iocp, "
                     "error code %lu", GetLastError());
        return FALSE;
    }

    GHashTableIter iter;
    gpointer value = NULL;
    gpointer key = NULL;

    g_hash_table_iter_init (&iter, priv->handle_hash);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        if (!add_handle_to_iocp(monitor, (HANDLE)value)) {
            seaf_warning("Failed to add dir handle to iocp, "
                         "repo %s, error code %lu", (char *)key,
                         GetLastError());
            continue;
        }
    }

    seaf_debug("Done: add_all_to_iocp\n");
    return TRUE;
}