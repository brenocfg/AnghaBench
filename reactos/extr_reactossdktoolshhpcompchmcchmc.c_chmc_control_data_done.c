#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct chmcTreeNode {int /*<<< orphan*/  flags; } ;
struct chmcFile {TYPE_1__** sections; } ;
typedef  int /*<<< orphan*/  UChar ;
struct TYPE_2__ {int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int CHMC_ENOMEM ; 
 int CHMC_NOERR ; 
 int /*<<< orphan*/  CHMC_TNFL_STATIC ; 
 int /*<<< orphan*/  _CHMC_LZXC_V2_LEN ; 
 struct chmcTreeNode* chmc_add_meta (struct chmcFile*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int chmc_control_data_done(struct chmcFile *chm)
{
	struct chmcTreeNode *ctrl;

	ctrl = chmc_add_meta(chm, "::DataSpace/Storage/MSCompressed/ControlData",
	                     0, (UChar *)&chm->sections[1]->control_data,
	                     _CHMC_LZXC_V2_LEN);

	if (ctrl) {
		ctrl->flags |= CHMC_TNFL_STATIC;
		return CHMC_NOERR;
	}

	return CHMC_ENOMEM;
}