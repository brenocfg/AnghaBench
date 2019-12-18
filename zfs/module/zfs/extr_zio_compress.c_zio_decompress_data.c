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
typedef  enum zio_compress { ____Placeholder_zio_compress } zio_compress ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 void* abd_borrow_buf_copy (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ spa_get_random (scalar_t__) ; 
 int zio_decompress_data_buf (int,void*,void*,size_t,size_t) ; 
 scalar_t__ zio_decompress_fail_fraction ; 

int
zio_decompress_data(enum zio_compress c, abd_t *src, void *dst,
    size_t s_len, size_t d_len)
{
	void *tmp = abd_borrow_buf_copy(src, s_len);
	int ret = zio_decompress_data_buf(c, tmp, dst, s_len, d_len);
	abd_return_buf(src, tmp, s_len);

	/*
	 * Decompression shouldn't fail, because we've already verified
	 * the checksum.  However, for extra protection (e.g. against bitflips
	 * in non-ECC RAM), we handle this error (and test it).
	 */
	ASSERT0(ret);
	if (zio_decompress_fail_fraction != 0 &&
	    spa_get_random(zio_decompress_fail_fraction) == 0)
		ret = SET_ERROR(EINVAL);

	return (ret);
}