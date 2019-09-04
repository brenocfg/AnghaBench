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
struct chmcTreeNode {int dummy; } ;
struct chmcFile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct chmcFile*) ; 
 struct chmcTreeNode* chmc_add_entry (struct chmcFile*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct chmcTreeNode *chmc_add_empty(struct chmcFile *chm, const char *file)
{
	assert(chm);
	return chmc_add_entry(chm, file, 0, 0, NULL, 0, 0);
}