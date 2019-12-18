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
struct modlmisc {int dummy; } ;
struct modlinkage {scalar_t__ ml_rev; int /*<<< orphan*/ * ml_linkage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 int EINVAL ; 
 int MODL_INSTALL (struct modlmisc*,struct modlinkage*) ; 
 int /*<<< orphan*/  MODL_REMOVE (struct modlmisc*,struct modlinkage*) ; 
 scalar_t__ MODREV_1 ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*) ; 

int
mod_install(struct modlinkage *modlp)
{
	int retval = -1;	/* No linkage structures */
	struct modlmisc **linkpp;
	struct modlmisc **linkpp1;

	if (modlp->ml_rev != MODREV_1) {
		cmn_err(CE_WARN, "mod_install: "
		    "modlinkage structure is not MODREV_1\n");
		return (EINVAL);
	}
	linkpp = (struct modlmisc **)&modlp->ml_linkage[0];

	while (*linkpp != NULL) {
		if ((retval = MODL_INSTALL(*linkpp, modlp)) != 0) {
			linkpp1 = (struct modlmisc **)&modlp->ml_linkage[0];

			while (linkpp1 != linkpp) {
				MODL_REMOVE(*linkpp1, modlp); /* clean up */
				linkpp1++;
			}
			break;
		}
		linkpp++;
	}
	return (retval);
}