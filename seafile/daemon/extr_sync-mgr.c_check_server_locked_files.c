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
typedef  void* gpointer ;
struct TYPE_4__ {int /*<<< orphan*/  http_server_states; } ;
typedef  TYPE_1__ SeafSyncManager ;
typedef  int /*<<< orphan*/  HttpServerState ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  check_locked_files_one_server (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,void**,void**) ; 

__attribute__((used)) static void
check_server_locked_files (SeafSyncManager *mgr, GList *repos)
{
    GHashTableIter iter;
    gpointer key, value;
    char *host;
    HttpServerState *state;

    g_hash_table_iter_init (&iter, mgr->http_server_states);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        host = key;
        state = value;
        check_locked_files_one_server (mgr, host, state, repos);
    }
}