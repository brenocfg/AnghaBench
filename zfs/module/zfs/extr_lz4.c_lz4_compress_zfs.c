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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  bufsiz ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BE_32 (scalar_t__) ; 
 scalar_t__ real_LZ4_compress (void*,char*,size_t,size_t) ; 

size_t
lz4_compress_zfs(void *s_start, void *d_start, size_t s_len,
    size_t d_len, int n)
{
	uint32_t bufsiz;
	char *dest = d_start;

	ASSERT(d_len >= sizeof (bufsiz));

	bufsiz = real_LZ4_compress(s_start, &dest[sizeof (bufsiz)], s_len,
	    d_len - sizeof (bufsiz));

	/* Signal an error if the compression routine returned zero. */
	if (bufsiz == 0)
		return (s_len);

	/*
	 * The exact compressed size is needed by the decompression routine,
	 * so it is stored at the start of the buffer. Note that this may be
	 * less than the compressed block size, which is rounded up to a
	 * multiple of 1<<ashift.
	 */
	*(uint32_t *)dest = BE_32(bufsiz);

	return (bufsiz + sizeof (bufsiz));
}