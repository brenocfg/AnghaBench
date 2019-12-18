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
typedef  int /*<<< orphan*/  gint64 ;

/* Variables and functions */
 char* gen_conflict_path (char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_file_modifier_mtime (char const*,char const*,int,char const*,char const*,char**,int /*<<< orphan*/ *) ; 

char *
gen_conflict_path_wrapper (const char *repo_id, int version,
                           const char *head, const char *in_repo_path,
                           const char *original_path)
{
    char *modifier;
    gint64 mtime;

    /* XXX: this function is only used in client, so store_id is always
     * the same as repo_id. This can be changed if it's also called in
     * server.
     */
    if (get_file_modifier_mtime (repo_id, repo_id, version, head, in_repo_path,
                                 &modifier, &mtime) < 0)
        return NULL;

    return gen_conflict_path (original_path, modifier, mtime);
}