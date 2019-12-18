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
struct modspecific_info {char* msi_linkinfo; int /*<<< orphan*/  msi_p0; } ;
struct modlmisc {int /*<<< orphan*/  misc_linkinfo; } ;
struct modlinkage {scalar_t__ ml_linkage; int /*<<< orphan*/  ml_rev; } ;
struct modinfo {scalar_t__ mi_info; void* mi_base; struct modspecific_info* mi_msinfo; int /*<<< orphan*/  mi_rev; } ;

/* Variables and functions */
 scalar_t__ MI_INFO_LINKAGE ; 
 int MODL_INFO (struct modlmisc*,struct modlinkage*,int /*<<< orphan*/ *) ; 
 int MODMAXLINK ; 
 int /*<<< orphan*/  MODMAXLINKINFOLEN ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mod_info(struct modlinkage *modlp, struct modinfo *modinfop)
{
	int i;
	int retval = 0;
	struct modspecific_info *msip;
	struct modlmisc **linkpp;

	modinfop->mi_rev = modlp->ml_rev;

	linkpp = (struct modlmisc **)modlp->ml_linkage;
	msip = &modinfop->mi_msinfo[0];

	for (i = 0; i < MODMAXLINK; i++) {
		if (*linkpp == NULL) {
			msip->msi_linkinfo[0] = '\0';
		} else {
			(void) strlcpy(msip->msi_linkinfo,
			    (*linkpp)->misc_linkinfo, MODMAXLINKINFOLEN);
			retval = MODL_INFO(*linkpp, modlp, &msip->msi_p0);
			if (retval != 0)
				break;
			linkpp++;
		}
		msip++;
	}

	if (modinfop->mi_info == MI_INFO_LINKAGE) {
		/*
		 * Slight kludge used to extract the address of the
		 * modlinkage structure from the module (just after
		 * loading a module for the very first time)
		 */
		modinfop->mi_base = (void *)modlp;
	}

	if (retval == 0)
		return (1);
	return (0);
}