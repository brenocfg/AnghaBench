#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  scalar_t__ gint ;
typedef  TYPE_1__* gconstpointer ;
struct TYPE_5__ {scalar_t__ ctime; } ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */

__attribute__((used)) static gint
compare_commit_by_time (gconstpointer a, gconstpointer b, gpointer unused)
{
    const SeafCommit *commit_a = a;
    const SeafCommit *commit_b = b;

    /* Latest commit comes first in the list. */
    return (commit_b->ctime - commit_a->ctime);
}