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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  commit_id; } ;
typedef  TYPE_1__ SeafCommit ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ *,char*,char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
add_to_commit_hash (SeafCommit *commit, void *vhash, gboolean *stop)
{
    GHashTable *hash = vhash;

    char *key = g_strdup (commit->commit_id);
    g_hash_table_replace (hash, key, key);

    return TRUE;
}