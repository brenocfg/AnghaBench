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
struct input_ctx {scalar_t__ input_space; int /*<<< orphan*/  input_buf; int /*<<< orphan*/  since_ground; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ INPUT_BUF_START ; 
 int /*<<< orphan*/  evbuffer_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
input_ground(struct input_ctx *ictx)
{
	event_del(&ictx->timer);
	evbuffer_drain(ictx->since_ground, EVBUFFER_LENGTH(ictx->since_ground));

	if (ictx->input_space > INPUT_BUF_START) {
		ictx->input_space = INPUT_BUF_START;
		ictx->input_buf = xrealloc(ictx->input_buf, INPUT_BUF_START);
	}
}