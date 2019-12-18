#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  http_tx_mgr; } ;
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  server_url; int /*<<< orphan*/  effective_url; int /*<<< orphan*/  http_protocol_version; } ;
struct TYPE_9__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  version; int /*<<< orphan*/  not_supported; scalar_t__ check_success; } ;
typedef  TYPE_1__ HttpProtocolVersion ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_STATE_CANCELED ; 
 scalar_t__ CLONE_STATE_CANCEL_PENDING ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_http_fileserver_protocol_done ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_check_head_commit (TYPE_2__*) ; 
 char* http_fileserver_url (int /*<<< orphan*/ ) ; 
 scalar_t__ http_tx_manager_check_protocol_version (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__* seaf ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  transition_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_to_error (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_http_protocol_done (HttpProtocolVersion *result, void *user_data)
{
    CloneTask *task = user_data;

    if (task->state == CLONE_STATE_CANCEL_PENDING) {
        transition_state (task, CLONE_STATE_CANCELED);
        return;
    }

    if (result->check_success && !result->not_supported) {
        task->http_protocol_version = result->version;
        task->effective_url = g_strdup(task->server_url);
        http_check_head_commit (task);
    } else if (strncmp(task->server_url, "https", 5) != 0) {
        char *host_fileserver = http_fileserver_url(task->server_url);
        if (http_tx_manager_check_protocol_version (seaf->http_tx_mgr,
                                                    host_fileserver,
                                                    TRUE,
                                                    check_http_fileserver_protocol_done,
                                                    task) < 0)
            transition_to_error (task, SYNC_ERROR_ID_NOT_ENOUGH_MEMORY);
        g_free (host_fileserver);
    } else {
        /* Wait for periodic retry. */
        transition_to_error (task, result->error_code);
    }
}