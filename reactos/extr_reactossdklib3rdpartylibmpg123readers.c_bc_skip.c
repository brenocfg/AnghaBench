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
struct bufferchain {scalar_t__ size; scalar_t__ pos; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ READER_ERROR ; 
 scalar_t__ bc_need_more (struct bufferchain*) ; 

__attribute__((used)) static ssize_t bc_skip(struct bufferchain *bc, ssize_t count)
{
	if(count >= 0)
	{
		if(bc->size - bc->pos < count) return bc_need_more(bc);
		else return bc->pos += count;
	}
	else return READER_ERROR;
}