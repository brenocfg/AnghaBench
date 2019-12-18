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
struct input_ctx {int interm_len; char* interm_buf; char ch; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_DISCARD ; 

__attribute__((used)) static int
input_intermediate(struct input_ctx *ictx)
{
	if (ictx->interm_len == (sizeof ictx->interm_buf) - 1)
		ictx->flags |= INPUT_DISCARD;
	else {
		ictx->interm_buf[ictx->interm_len++] = ictx->ch;
		ictx->interm_buf[ictx->interm_len] = '\0';
	}

	return (0);
}