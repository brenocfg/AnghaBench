#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCCompareResult ;
struct TYPE_9__ {int /*<<< orphan*/  commit_mgr; } ;
struct TYPE_8__ {char const* commit_id; } ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/  VC_FAST_FORWARD ; 
 int /*<<< orphan*/  VC_INDEPENDENT ; 
 int /*<<< orphan*/  VC_UP_TO_DATE ; 
 TYPE_1__* get_merge_base (TYPE_1__*,TYPE_1__*) ; 
 TYPE_4__* seaf ; 
 TYPE_1__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

VCCompareResult
vc_compare_commits (const char *repo_id, int version,
                    const char *c1, const char *c2)
{
    SeafCommit *commit1, *commit2, *ca;
    VCCompareResult ret;

    /* Treat the same as up-to-date. */
    if (strcmp (c1, c2) == 0)
        return VC_UP_TO_DATE;

    commit1 = seaf_commit_manager_get_commit (seaf->commit_mgr, repo_id, version, c1);
    if (!commit1)
        return VC_INDEPENDENT;

    commit2 = seaf_commit_manager_get_commit (seaf->commit_mgr, repo_id, version, c2);
    if (!commit2) {
        seaf_commit_unref (commit1);
        return VC_INDEPENDENT;
    }

    ca = get_merge_base (commit1, commit2);

    if (!ca)
        ret = VC_INDEPENDENT;
    else if (strcmp(ca->commit_id, commit1->commit_id) == 0)
        ret = VC_UP_TO_DATE;
    else if (strcmp(ca->commit_id, commit2->commit_id) == 0)
        ret = VC_FAST_FORWARD;
    else
        ret = VC_INDEPENDENT;

    if (ca) seaf_commit_unref (ca);
    seaf_commit_unref (commit1);
    seaf_commit_unref (commit2);
    return ret;
}