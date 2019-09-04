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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bb_error_msg (char*) ; 
 char* bb_virtual_buf ; 
 int bb_virtual_fd ; 
 size_t bb_virtual_len ; 
 scalar_t__ bb_virtual_pos ; 
 int /*<<< orphan*/  bled_initialized ; 
 int bled_uncompress_to_buffer (char*,char*,size_t,int) ; 

int64_t bled_uncompress_from_buffer_to_buffer(const char* src, const size_t src_len, char* dst, size_t dst_len, int type)
{
	int64_t ret;

	if (!bled_initialized) {
		bb_error_msg("The library has not been initialized");
		return -1;
	}

	if ((src == NULL) || (dst == NULL)) {
		bb_error_msg("Invalid parameter");
		return -1;
	}

	if (bb_virtual_buf != NULL) {
		bb_error_msg("Can not decompress more than one buffer at once");
		return -1;
	}

	bb_virtual_buf = (char*)src;
	bb_virtual_len = src_len;
	bb_virtual_pos = 0;
	bb_virtual_fd = 0;

	ret = bled_uncompress_to_buffer("", dst, dst_len, type);

	bb_virtual_buf = NULL;
	bb_virtual_len = 0;
	bb_virtual_fd = -1;

	return ret;
}