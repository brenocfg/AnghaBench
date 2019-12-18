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
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  zc_byteswap ;
typedef  int /*<<< orphan*/  zc ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct abd {int dummy; } ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ NANOSEC ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 struct abd* abd_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf_off (struct abd*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abd_fletcher_4_byteswap (struct abd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_fletcher_4_native (struct abd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_free (struct abd*) ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fletcher_4_byteswap (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_impl_set (char*) ; 
 int /*<<< orphan*/  fletcher_4_native (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gethrtime () ; 
 void* umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (void*,int) ; 
 int ztest_random (int /*<<< orphan*/ ) ; 
 int ztest_random_blocksize () ; 

void
ztest_fletcher(ztest_ds_t *zd, uint64_t id)
{
	hrtime_t end = gethrtime() + NANOSEC;

	while (gethrtime() <= end) {
		int run_count = 100;
		void *buf;
		struct abd *abd_data, *abd_meta;
		uint32_t size;
		int *ptr;
		int i;
		zio_cksum_t zc_ref;
		zio_cksum_t zc_ref_byteswap;

		size = ztest_random_blocksize();

		buf = umem_alloc(size, UMEM_NOFAIL);
		abd_data = abd_alloc(size, B_FALSE);
		abd_meta = abd_alloc(size, B_TRUE);

		for (i = 0, ptr = buf; i < size / sizeof (*ptr); i++, ptr++)
			*ptr = ztest_random(UINT_MAX);

		abd_copy_from_buf_off(abd_data, buf, 0, size);
		abd_copy_from_buf_off(abd_meta, buf, 0, size);

		VERIFY0(fletcher_4_impl_set("scalar"));
		fletcher_4_native(buf, size, NULL, &zc_ref);
		fletcher_4_byteswap(buf, size, NULL, &zc_ref_byteswap);

		VERIFY0(fletcher_4_impl_set("cycle"));
		while (run_count-- > 0) {
			zio_cksum_t zc;
			zio_cksum_t zc_byteswap;

			fletcher_4_byteswap(buf, size, NULL, &zc_byteswap);
			fletcher_4_native(buf, size, NULL, &zc);

			VERIFY0(bcmp(&zc, &zc_ref, sizeof (zc)));
			VERIFY0(bcmp(&zc_byteswap, &zc_ref_byteswap,
			    sizeof (zc_byteswap)));

			/* Test ABD - data */
			abd_fletcher_4_byteswap(abd_data, size, NULL,
			    &zc_byteswap);
			abd_fletcher_4_native(abd_data, size, NULL, &zc);

			VERIFY0(bcmp(&zc, &zc_ref, sizeof (zc)));
			VERIFY0(bcmp(&zc_byteswap, &zc_ref_byteswap,
			    sizeof (zc_byteswap)));

			/* Test ABD - metadata */
			abd_fletcher_4_byteswap(abd_meta, size, NULL,
			    &zc_byteswap);
			abd_fletcher_4_native(abd_meta, size, NULL, &zc);

			VERIFY0(bcmp(&zc, &zc_ref, sizeof (zc)));
			VERIFY0(bcmp(&zc_byteswap, &zc_ref_byteswap,
			    sizeof (zc_byteswap)));

		}

		umem_free(buf, size);
		abd_free(abd_data);
		abd_free(abd_meta);
	}
}