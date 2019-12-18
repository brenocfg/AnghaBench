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
typedef  int uint64_t ;
struct send_range {scalar_t__ eos_marker; int object; scalar_t__ type; int start_blkid; int end_blkid; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int DNODES_PER_BLOCK_SHIFT ; 
 scalar_t__ HOLE ; 
 scalar_t__ OBJECT ; 
 scalar_t__ OBJECT_RANGE ; 
 int TREE_CMP (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __attribute__((unused))
send_range_after(const struct send_range *from, const struct send_range *to)
{
	if (from->eos_marker == B_TRUE)
		return (1);
	if (to->eos_marker == B_TRUE)
		return (-1);

	uint64_t from_obj = from->object;
	uint64_t from_end_obj = from->object + 1;
	uint64_t to_obj = to->object;
	uint64_t to_end_obj = to->object + 1;
	if (from_obj == 0) {
		ASSERT(from->type == HOLE || from->type == OBJECT_RANGE);
		from_obj = from->start_blkid << DNODES_PER_BLOCK_SHIFT;
		from_end_obj = from->end_blkid << DNODES_PER_BLOCK_SHIFT;
	}
	if (to_obj == 0) {
		ASSERT(to->type == HOLE || to->type == OBJECT_RANGE);
		to_obj = to->start_blkid << DNODES_PER_BLOCK_SHIFT;
		to_end_obj = to->end_blkid << DNODES_PER_BLOCK_SHIFT;
	}

	if (from_end_obj <= to_obj)
		return (-1);
	if (from_obj >= to_end_obj)
		return (1);
	int64_t cmp = TREE_CMP(to->type == OBJECT_RANGE, from->type ==
	    OBJECT_RANGE);
	if (unlikely(cmp))
		return (cmp);
	cmp = TREE_CMP(to->type == OBJECT, from->type == OBJECT);
	if (unlikely(cmp))
		return (cmp);
	if (from->end_blkid <= to->start_blkid)
		return (-1);
	if (from->start_blkid >= to->end_blkid)
		return (1);
	return (0);
}