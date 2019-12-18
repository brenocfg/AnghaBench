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
 void* abd_borrow_buf (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  abd_copy_to_buf (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  abd_is_linear (int /*<<< orphan*/ *) ; 

void *
abd_borrow_buf_copy(abd_t *abd, size_t n)
{
	void *buf = abd_borrow_buf(abd, n);
	if (!abd_is_linear(abd)) {
		abd_copy_to_buf(buf, abd, n);
	}
	return (buf);
}