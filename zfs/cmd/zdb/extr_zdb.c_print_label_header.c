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
struct TYPE_3__ {scalar_t__ header_printed; } ;
typedef  TYPE_1__ zdb_label_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 scalar_t__* dump_opt ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_label_header(zdb_label_t *label, int l)
{

	if (dump_opt['q'])
		return;

	if (label->header_printed == B_TRUE)
		return;

	(void) printf("------------------------------------\n");
	(void) printf("LABEL %d\n", l);
	(void) printf("------------------------------------\n");

	label->header_printed = B_TRUE;
}