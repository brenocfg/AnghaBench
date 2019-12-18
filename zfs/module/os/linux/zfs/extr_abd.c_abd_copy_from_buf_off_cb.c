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
struct buf_arg {char* arg_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 

__attribute__((used)) static int
abd_copy_from_buf_off_cb(void *buf, size_t size, void *private)
{
	struct buf_arg *ba_ptr = private;

	(void) memcpy(buf, ba_ptr->arg_buf, size);
	ba_ptr->arg_buf = (char *)ba_ptr->arg_buf + size;

	return (0);
}