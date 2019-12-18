#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_7__ {scalar_t__* cmd_pipe; TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  iocp_handle; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateIoCompletionPort (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_watch_cmd_pipe (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_watch_dir_change (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static BOOL
add_handle_to_iocp (SeafWTMonitor *monitor, HANDLE hAdd)
{
    SeafWTMonitorPriv *priv = monitor->priv;
    
    if (!priv || !hAdd)
        return FALSE;

    /* CreateIoCompletionPort() will add the handle to an I/O Completion Port
      if the iocp handle is not NULL. Otherwise it will create a new IOCP
      handle.

      The `key' parameter is used by th IOCP to tell us which handle watched
      by the I/O Completion Port triggeed a return of the
      GetQueuedCompletionStatus() function.

      Here we use the value of the handle itself as the key for this handle
      in the I/O Completion Port.
    */
    priv->iocp_handle = CreateIoCompletionPort
        (hAdd,                  /* handle to add */
         priv->iocp_handle,     /* iocp handle */
         (ULONG_PTR)hAdd,       /* key for this handle */
         1);                    /* Num of concurrent threads */

    if (!priv->iocp_handle) {
        seaf_warning ("failed to create/add iocp, error code %lu",
                      GetLastError());
        return FALSE;
    }

    if (hAdd == (HANDLE)monitor->cmd_pipe[0]) {
        /* HANDLE is cmd_pipe */
        return start_watch_cmd_pipe (monitor, NULL);
    } else {
        /* HANDLE is a dir handle */
        return start_watch_dir_change (priv, hAdd);
    }

}