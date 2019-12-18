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

/* Variables and functions */
 int /*<<< orphan*/  SSH_CACHE_FILE ; 
 int /*<<< orphan*/  cache_dir ; 
 char* g_build_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  history_remove (char*,char const*) ; 

__attribute__((used)) static void delete_ssh ( const char *host )
{
    if ( !host || !host[0] ) {
        return;
    }
    char *path = g_build_filename ( cache_dir, SSH_CACHE_FILE, NULL );
    history_remove ( path, host );
    g_free ( path );
}