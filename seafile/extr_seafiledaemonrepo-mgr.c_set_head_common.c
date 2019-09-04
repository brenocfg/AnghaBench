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
struct TYPE_3__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  seaf_branch_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_branch_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_head_common (SeafRepo *repo, SeafBranch *branch)
{
    if (repo->head)
        seaf_branch_unref (repo->head);
    repo->head = branch;
    seaf_branch_ref(branch);
}