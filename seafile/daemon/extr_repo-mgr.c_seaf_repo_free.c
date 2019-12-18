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
struct TYPE_4__ {struct TYPE_4__* token; struct TYPE_4__* email; struct TYPE_4__* relay_id; struct TYPE_4__* worktree; struct TYPE_4__* category; struct TYPE_4__* desc; struct TYPE_4__* name; scalar_t__ head; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_branch_unref (scalar_t__) ; 

void
seaf_repo_free (SeafRepo *repo)
{
    if (repo->head) seaf_branch_unref (repo->head);

    g_free (repo->name);
    g_free (repo->desc);
    g_free (repo->category);
    g_free (repo->worktree);
    g_free (repo->relay_id);
    g_free (repo->email);
    g_free (repo->token);
    g_free (repo);
}