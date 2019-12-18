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
typedef  int /*<<< orphan*/  SeafStat ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 int /*<<< orphan*/  apply_to_tree (int /*<<< orphan*/ *,char,unsigned char*,int /*<<< orphan*/ *,char const*,char const*,char const*) ; 

void
add_to_changeset (ChangeSet *changeset,
                  char status,
                  unsigned char *sha1,
                  SeafStat *st,
                  const char *modifier,
                  const char *path,
                  const char *new_path)
{
    apply_to_tree (changeset,
                   status, sha1, st, modifier, path, new_path);
}