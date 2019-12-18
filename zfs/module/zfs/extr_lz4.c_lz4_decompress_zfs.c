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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bufsiz ;

/* Variables and functions */
 int BE_IN32 (char const*) ; 
 scalar_t__ LZ4_uncompress_unknownOutputSize (char const*,void*,int,size_t) ; 

int
lz4_decompress_zfs(void *s_start, void *d_start, size_t s_len,
    size_t d_len, int n)
{
	const char *src = s_start;
	uint32_t bufsiz = BE_IN32(src);

	/* invalid compressed buffer size encoded at start */
	if (bufsiz + sizeof (bufsiz) > s_len)
		return (1);

	/*
	 * Returns 0 on success (decompression function returned non-negative)
	 * and non-zero on failure (decompression function returned negative).
	 */
	return (LZ4_uncompress_unknownOutputSize(&src[sizeof (bufsiz)],
	    d_start, bufsiz, d_len) < 0);
}