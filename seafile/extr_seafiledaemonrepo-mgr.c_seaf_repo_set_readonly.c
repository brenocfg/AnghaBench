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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  manager; int /*<<< orphan*/  is_readonly; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_PROP_IS_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  save_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
seaf_repo_set_readonly (SeafRepo *repo)
{
    repo->is_readonly = TRUE;
    save_repo_property (repo->manager, repo->id, REPO_PROP_IS_READONLY, "true");
}