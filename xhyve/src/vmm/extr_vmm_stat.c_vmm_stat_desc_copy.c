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
struct vmm_stat_type {int index; int nelems; char* desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int vst_num_types ; 
 struct vmm_stat_type** vsttab ; 

int
vmm_stat_desc_copy(int index, char *buf, size_t bufsize)
{
	int i;
	struct vmm_stat_type *vst;

	for (i = 0; i < vst_num_types; i++) {
		vst = vsttab[i];
		if (index >= vst->index && index < vst->index + vst->nelems) {
			if (vst->nelems > 1) {
				snprintf(buf, bufsize, "%s[%d]",
					 vst->desc, index - vst->index);
			} else {
				strlcpy(buf, vst->desc, bufsize);
			}
			return (0);	/* found it */
		}
	}

	return (EINVAL);
}