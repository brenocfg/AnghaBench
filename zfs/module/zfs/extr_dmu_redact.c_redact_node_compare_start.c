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
struct redact_record {int /*<<< orphan*/  datablksz; int /*<<< orphan*/  start_blkid; int /*<<< orphan*/  start_object; scalar_t__ eos_marker; } ;
struct redact_node {scalar_t__ thread_num; struct redact_record* record; } ;

/* Variables and functions */
 int redact_range_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
redact_node_compare_start(const void *arg1, const void *arg2)
{
	const struct redact_node *rn1 = arg1;
	const struct redact_node *rn2 = arg2;
	const struct redact_record *rr1 = rn1->record;
	const struct redact_record *rr2 = rn2->record;
	if (rr1->eos_marker)
		return (1);
	if (rr2->eos_marker)
		return (-1);

	int cmp = redact_range_compare(rr1->start_object, rr1->start_blkid,
	    rr1->datablksz, rr2->start_object, rr2->start_blkid,
	    rr2->datablksz);
	if (cmp == 0)
		cmp = (rn1->thread_num < rn2->thread_num ? -1 : 1);
	return (cmp);
}