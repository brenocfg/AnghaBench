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

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINTR ; 
 int _read (int,void*,int) ; 
 int bb_total_rb ; 
 int /*<<< orphan*/ * bb_virtual_buf ; 
 int bb_virtual_fd ; 
 size_t bb_virtual_len ; 
 size_t bb_virtual_pos ; 
 scalar_t__* bled_cancel_request ; 
 int /*<<< orphan*/  bled_progress (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline int full_read(int fd, void *buf, size_t count) {
	int rb;

	if (fd < 0) {
		errno = EBADF;
		return -1;
	}
	if (buf == NULL) {
		errno = EFAULT;
		return -1;
	}
	if ((bled_cancel_request != NULL) && (*bled_cancel_request != 0)) {
		errno = EINTR;
		return -1;
	}

	if (fd == bb_virtual_fd) {
		if (bb_virtual_pos + count > bb_virtual_len)
			count = bb_virtual_len - bb_virtual_pos;
		memcpy(buf, &bb_virtual_buf[bb_virtual_pos], count);
		bb_virtual_pos += count;
		rb = (int)count;
	} else {
		rb = _read(fd, buf, (int)count);
	}
	if (rb > 0) {
		bb_total_rb += rb;
		if (bled_progress != NULL)
			bled_progress(bb_total_rb);
	}
	return rb;
}