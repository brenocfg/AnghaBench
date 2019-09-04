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
struct input_ctx {char* interm_buf; char* param_buf; char* input_buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  input_end; scalar_t__ input_len; scalar_t__ param_len; scalar_t__ interm_len; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_DISCARD ; 
 int /*<<< orphan*/  INPUT_END_ST ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
input_clear(struct input_ctx *ictx)
{
	event_del(&ictx->timer);

	*ictx->interm_buf = '\0';
	ictx->interm_len = 0;

	*ictx->param_buf = '\0';
	ictx->param_len = 0;

	*ictx->input_buf = '\0';
	ictx->input_len = 0;

	ictx->input_end = INPUT_END_ST;

	ictx->flags &= ~INPUT_DISCARD;
}