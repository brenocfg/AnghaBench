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
struct bufferchain {scalar_t__ fileoff; scalar_t__ firstpos; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/ * first; int /*<<< orphan*/ * last; } ;

/* Variables and functions */

__attribute__((used)) static void bc_init(struct bufferchain *bc)
{
	bc->first = NULL;
	bc->last  = bc->first;
	bc->size  = 0;
	bc->pos   = 0;
	bc->firstpos = 0;
	bc->fileoff  = 0;
}