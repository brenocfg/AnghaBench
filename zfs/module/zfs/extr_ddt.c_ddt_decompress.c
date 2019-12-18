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
struct TYPE_3__ {int /*<<< orphan*/  ci_level; int /*<<< orphan*/  (* ci_decompress ) (int*,void*,size_t,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ zio_compress_info_t ;
typedef  int uchar_t ;

/* Variables and functions */
 int DDT_COMPRESS_BYTEORDER_MASK ; 
 int DDT_COMPRESS_FUNCTION_MASK ; 
 scalar_t__ ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  bcopy (int*,void*,size_t) ; 
 int /*<<< orphan*/  byteswap_uint64_array (void*,size_t) ; 
 int /*<<< orphan*/  stub1 (int*,void*,size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* zio_compress_table ; 

void
ddt_decompress(uchar_t *src, void *dst, size_t s_len, size_t d_len)
{
	uchar_t version = *src++;
	int cpfunc = version & DDT_COMPRESS_FUNCTION_MASK;
	zio_compress_info_t *ci = &zio_compress_table[cpfunc];

	if (ci->ci_decompress != NULL)
		(void) ci->ci_decompress(src, dst, s_len, d_len, ci->ci_level);
	else
		bcopy(src, dst, d_len);

	if (((version & DDT_COMPRESS_BYTEORDER_MASK) != 0) !=
	    (ZFS_HOST_BYTEORDER != 0))
		byteswap_uint64_array(dst, d_len);
}