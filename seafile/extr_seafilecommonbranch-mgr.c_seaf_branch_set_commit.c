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
struct TYPE_3__ {char* commit_id; } ;
typedef  TYPE_1__ SeafBranch ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

void
seaf_branch_set_commit (SeafBranch *branch, const char *commit_id)
{
    memcpy (branch->commit_id, commit_id, 40);
    branch->commit_id[40] = '\0';
}