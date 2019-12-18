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
struct TYPE_4__ {char* hostname; scalar_t__ port; } ;
typedef  TYPE_1__ SshEntry ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_CACHE_FILE ; 
 int /*<<< orphan*/  cache_dir ; 
 int /*<<< orphan*/  execshssh (TYPE_1__ const*) ; 
 char* g_build_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  history_set (char*,char*) ; 

__attribute__((used)) static void exec_ssh ( const SshEntry *entry )
{
    if ( !(entry->hostname )|| !(entry->hostname[0]) ) {
        return;
    }

    if ( !execshssh ( entry ) ) {
        return;
    }

    //  This happens in non-critical time (After launching app)
    //  It is allowed to be a bit slower.
    char *path = g_build_filename ( cache_dir, SSH_CACHE_FILE, NULL );
    // TODO update.
    if ( entry->port > 0 ) {
        char *store = g_strdup_printf("%s\x1F%d", entry->hostname, entry->port );
        history_set ( path, store );
        g_free ( store );
    } else {
        history_set ( path, entry->hostname );
    }
    g_free ( path );
}