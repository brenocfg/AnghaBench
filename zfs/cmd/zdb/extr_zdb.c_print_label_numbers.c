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
struct TYPE_3__ {scalar_t__* labels; } ;
typedef  TYPE_1__ cksum_record_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int VDEV_LABELS ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_label_numbers(char *prefix, cksum_record_t *rec)
{
	printf("%s", prefix);
	for (int i = 0; i < VDEV_LABELS; i++)
		if (rec->labels[i] == B_TRUE)
			printf("%d ", i);
	printf("\n");
}