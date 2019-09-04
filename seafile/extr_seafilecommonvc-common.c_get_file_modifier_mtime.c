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
 int get_file_modifier_mtime_v0 (char const*,char const*,int,char const*,char const*,char**,int /*<<< orphan*/ *) ; 
 int get_file_modifier_mtime_v1 (char const*,char const*,int,char const*,char const*,char**,int /*<<< orphan*/ *) ; 

int
get_file_modifier_mtime (const char *repo_id,
                         const char *store_id,
                         int version,
                         const char *head,
                         const char *path,
                         char **modifier,
                         gint64 *mtime)
{
    if (version > 0)
        return get_file_modifier_mtime_v1 (repo_id, store_id, version,
                                           head, path,
                                           modifier, mtime);
    else
        return get_file_modifier_mtime_v0 (repo_id, store_id, version,
                                           head, path,
                                           modifier, mtime);
}