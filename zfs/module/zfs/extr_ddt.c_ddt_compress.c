#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t (* ci_compress ) (void*,int*,size_t,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ci_level; } ;
typedef  TYPE_1__ zio_compress_info_t ;
typedef  int uchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDT_COMPRESS_BYTEORDER_MASK ; 
 scalar_t__ ZFS_HOST_BYTEORDER ; 
 int ZIO_COMPRESS_OFF ; 
 int ZIO_COMPRESS_ZLE ; 
 int /*<<< orphan*/  bcopy (void*,int*,size_t) ; 
 size_t stub1 (void*,int*,size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* zio_compress_table ; 

size_t
ddt_compress(void *src, uchar_t *dst, size_t s_len, size_t d_len)
{
	uchar_t *version = dst++;
	int cpfunc = ZIO_COMPRESS_ZLE;
	zio_compress_info_t *ci = &zio_compress_table[cpfunc];
	size_t c_len;

	ASSERT(d_len >= s_len + 1);	/* no compression plus version byte */

	c_len = ci->ci_compress(src, dst, s_len, d_len - 1, ci->ci_level);

	if (c_len == s_len) {
		cpfunc = ZIO_COMPRESS_OFF;
		bcopy(src, dst, s_len);
	}

	*version = cpfunc;
	/* CONSTCOND */
	if (ZFS_HOST_BYTEORDER)
		*version |= DDT_COMPRESS_BYTEORDER_MASK;

	return (c_len + 1);
}