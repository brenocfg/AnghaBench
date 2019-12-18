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
struct mem_seg {int /*<<< orphan*/ * object; int /*<<< orphan*/  len; int /*<<< orphan*/  gpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct mem_seg*,int) ; 
 int /*<<< orphan*/  vmm_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_free_mem_seg(struct mem_seg *seg)
{
	if (seg->object != NULL) {
		vmm_mem_free(seg->gpa, seg->len, seg->object);
	}

	bzero(seg, sizeof(*seg));
}