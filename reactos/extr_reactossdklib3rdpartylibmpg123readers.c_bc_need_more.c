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
struct bufferchain {scalar_t__ firstpos; scalar_t__ pos; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  READER_MORE ; 
 int /*<<< orphan*/  debug3 (char*,long,long,long) ; 

__attribute__((used)) static ssize_t bc_need_more(struct bufferchain *bc)
{
	debug3("hit end, back to beginning (%li - %li < %li)", (long)bc->size, (long)bc->pos, (long)bc->size);
	/* go back to firstpos, undo the previous reads */
	bc->pos = bc->firstpos;
	return READER_MORE;
}