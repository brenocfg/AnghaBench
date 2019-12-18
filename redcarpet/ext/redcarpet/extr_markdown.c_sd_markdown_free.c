#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd_markdown {TYPE_1__* work_bufs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * item; scalar_t__ asize; } ;

/* Variables and functions */
 size_t BUFFER_BLOCK ; 
 size_t BUFFER_SPAN ; 
 int /*<<< orphan*/  bufrelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sd_markdown*) ; 
 int /*<<< orphan*/  redcarpet_stack_free (TYPE_1__*) ; 

void
sd_markdown_free(struct sd_markdown *md)
{
	size_t i;

	for (i = 0; i < (size_t)md->work_bufs[BUFFER_SPAN].asize; ++i)
		bufrelease(md->work_bufs[BUFFER_SPAN].item[i]);

	for (i = 0; i < (size_t)md->work_bufs[BUFFER_BLOCK].asize; ++i)
		bufrelease(md->work_bufs[BUFFER_BLOCK].item[i]);

	redcarpet_stack_free(&md->work_bufs[BUFFER_SPAN]);
	redcarpet_stack_free(&md->work_bufs[BUFFER_BLOCK]);

	free(md);
}