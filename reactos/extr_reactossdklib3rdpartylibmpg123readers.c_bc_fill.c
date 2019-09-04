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
struct bufferchain {scalar_t__ pos; scalar_t__ size; } ;

/* Variables and functions */

size_t bc_fill(struct bufferchain *bc)
{
	return (size_t)(bc->size - bc->pos);
}