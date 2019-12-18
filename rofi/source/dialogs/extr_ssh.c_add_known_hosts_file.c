#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  user_known_hosts; } ;
typedef  TYPE_1__ SSHModePrivateData ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GCompareFunc ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*,char const*) ; 
 int /*<<< orphan*/  g_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_list_find_custom (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 

__attribute__((used)) static void add_known_hosts_file ( SSHModePrivateData *pd, const char *token )
{
    GList *item = g_list_find_custom ( pd->user_known_hosts, token, (GCompareFunc)g_strcmp0 );
    if ( item == NULL ) {
        g_debug("Add '%s' to UserKnownHost list", token);
        pd->user_known_hosts = g_list_append ( pd->user_known_hosts, g_strdup ( token ) );
    } else {
        g_debug("File '%s' already in UserKnownHostsFile list", token);
    }
}