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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  email; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_PROP_EMAIL ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  save_repo_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int
seaf_repo_manager_set_repo_email (SeafRepoManager *mgr,
                                  SeafRepo *repo,
                                  const char *email)
{
    g_free (repo->email);
    repo->email = g_strdup(email);

    save_repo_property (mgr, repo->id, REPO_PROP_EMAIL, email);
    return 0;
}