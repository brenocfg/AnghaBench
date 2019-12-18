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
struct scatterlist {int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sg_init_table(struct scatterlist *sg, int nr)
{
	memset(sg, 0, nr * sizeof (struct scatterlist));
	sg[nr - 1].end = 1;
}