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
struct input_ctx {size_t input_space; int input_len; char* input_buf; char ch; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t INPUT_BUF_LIMIT ; 
 int /*<<< orphan*/  INPUT_DISCARD ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static int
input_input(struct input_ctx *ictx)
{
	size_t available;

	available = ictx->input_space;
	while (ictx->input_len + 1 >= available) {
		available *= 2;
		if (available > INPUT_BUF_LIMIT) {
			ictx->flags |= INPUT_DISCARD;
			return (0);
		}
		ictx->input_buf = xrealloc(ictx->input_buf, available);
		ictx->input_space = available;
	}
	ictx->input_buf[ictx->input_len++] = ictx->ch;
	ictx->input_buf[ictx->input_len] = '\0';

	return (0);
}