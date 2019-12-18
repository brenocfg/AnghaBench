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
struct bufferchain {scalar_t__ pos; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ READER_ERROR ; 

__attribute__((used)) static ssize_t bc_seekback(struct bufferchain *bc, ssize_t count)
{
	if(count >= 0 && count <= bc->pos) return bc->pos -= count;
	else return READER_ERROR;
}