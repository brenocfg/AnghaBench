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
struct modlmisc {int /*<<< orphan*/  misc_linkinfo; } ;
struct modlinkage {int /*<<< orphan*/ * ml_linkage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 scalar_t__ MODL_INSTALL (struct modlmisc*,struct modlinkage*) ; 
 int MODL_REMOVE (struct modlmisc*,struct modlinkage*) ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reins_err ; 

int
mod_remove(struct modlinkage *modlp)
{
	int retval = 0;
	struct modlmisc **linkpp, *last_linkp;

	linkpp = (struct modlmisc **)&modlp->ml_linkage[0];

	while (*linkpp != NULL) {
		if ((retval = MODL_REMOVE(*linkpp, modlp)) != 0) {
			last_linkp = *linkpp;
			linkpp = (struct modlmisc **)&modlp->ml_linkage[0];
			while (*linkpp != last_linkp) {
				if (MODL_INSTALL(*linkpp, modlp) != 0) {
					cmn_err(CE_WARN, reins_err,
					    (*linkpp)->misc_linkinfo);
					break;
				}
				linkpp++;
			}
			break;
		}
		linkpp++;
	}
	return (retval);
}