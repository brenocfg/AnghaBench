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
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  abd_is_linear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,size_t) ; 

void
abd_return_buf_copy(abd_t *abd, void *buf, size_t n)
{
	if (!abd_is_linear(abd)) {
		abd_copy_from_buf(abd, buf, n);
	}
	abd_return_buf(abd, buf, n);
}