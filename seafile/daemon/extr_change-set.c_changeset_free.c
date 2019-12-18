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
struct TYPE_4__ {int /*<<< orphan*/  case_conflict_pattern; int /*<<< orphan*/  tree_root; } ;
typedef  TYPE_1__ ChangeSet ;

/* Variables and functions */
 int /*<<< orphan*/  changeset_dir_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_regex_unref (int /*<<< orphan*/ ) ; 

void
changeset_free (ChangeSet *changeset)
{
    if (!changeset)
        return;

    changeset_dir_free (changeset->tree_root);
    g_regex_unref (changeset->case_conflict_pattern);
    g_free (changeset);
}