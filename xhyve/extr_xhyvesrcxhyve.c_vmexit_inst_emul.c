#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vie {int num_valid; int* inst; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpa; int /*<<< orphan*/  paging; struct vie vie; } ;
struct TYPE_5__ {TYPE_1__ inst_emul; } ;
struct vm_exit {int /*<<< orphan*/  rip; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  vmexit_inst_emul; } ;

/* Variables and functions */
 int ESRCH ; 
 int VMEXIT_ABORT ; 
 int VMEXIT_CONTINUE ; 
 int emulate_mem (int,int /*<<< orphan*/ ,struct vie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__ stats ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
vmexit_inst_emul(struct vm_exit *vme, int *pvcpu)
{
	int err, i;
	struct vie *vie;

	stats.vmexit_inst_emul++;

	vie = &vme->u.inst_emul.vie;
	err = emulate_mem(*pvcpu, vme->u.inst_emul.gpa, vie,
		&vme->u.inst_emul.paging);

	if (err) {
		if (err == ESRCH) {
			fprintf(stderr, "Unhandled memory access to 0x%llx\n",
			    vme->u.inst_emul.gpa);
		}

		fprintf(stderr, "Failed to emulate instruction [");
		for (i = 0; i < vie->num_valid; i++) {
			fprintf(stderr, "0x%02x%s", vie->inst[i],
			    i != (vie->num_valid - 1) ? " " : "");
		}
		fprintf(stderr, "] at 0x%llx\n", vme->rip);
		return (VMEXIT_ABORT);
	}

	return (VMEXIT_CONTINUE);
}