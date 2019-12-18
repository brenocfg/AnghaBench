#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nvs_op; scalar_t__ nvs_recursion; int /*<<< orphan*/ * nvs_priv; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_10__ {int nvh_encoding; int nvh_endian; int /*<<< orphan*/  nvh_reserved2; int /*<<< orphan*/  nvh_reserved1; } ;
typedef  TYPE_2__ nvs_header_t ;
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_11__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_3__ nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
#define  NVS_OP_DECODE 132 
#define  NVS_OP_ENCODE 131 
#define  NVS_OP_GETSIZE 130 
#define  NV_ENCODE_NATIVE 129 
#define  NV_ENCODE_XDR 128 
 int nvs_native (TYPE_1__*,TYPE_3__*,char*,size_t*) ; 
 int nvs_xdr (TYPE_1__*,TYPE_3__*,char*,size_t*) ; 

__attribute__((used)) static int
nvlist_common(nvlist_t *nvl, char *buf, size_t *buflen, int encoding,
    int nvs_op)
{
	int err = 0;
	nvstream_t nvs;
	int nvl_endian;
#ifdef	_LITTLE_ENDIAN
	int host_endian = 1;
#else
	int host_endian = 0;
#endif	/* _LITTLE_ENDIAN */
	nvs_header_t *nvh = (void *)buf;

	if (buflen == NULL || nvl == NULL ||
	    (nvs.nvs_priv = (nvpriv_t *)(uintptr_t)nvl->nvl_priv) == NULL)
		return (EINVAL);

	nvs.nvs_op = nvs_op;
	nvs.nvs_recursion = 0;

	/*
	 * For NVS_OP_ENCODE and NVS_OP_DECODE make sure an nvlist and
	 * a buffer is allocated.  The first 4 bytes in the buffer are
	 * used for encoding method and host endian.
	 */
	switch (nvs_op) {
	case NVS_OP_ENCODE:
		if (buf == NULL || *buflen < sizeof (nvs_header_t))
			return (EINVAL);

		nvh->nvh_encoding = encoding;
		nvh->nvh_endian = nvl_endian = host_endian;
		nvh->nvh_reserved1 = 0;
		nvh->nvh_reserved2 = 0;
		break;

	case NVS_OP_DECODE:
		if (buf == NULL || *buflen < sizeof (nvs_header_t))
			return (EINVAL);

		/* get method of encoding from first byte */
		encoding = nvh->nvh_encoding;
		nvl_endian = nvh->nvh_endian;
		break;

	case NVS_OP_GETSIZE:
		nvl_endian = host_endian;

		/*
		 * add the size for encoding
		 */
		*buflen = sizeof (nvs_header_t);
		break;

	default:
		return (ENOTSUP);
	}

	/*
	 * Create an nvstream with proper encoding method
	 */
	switch (encoding) {
	case NV_ENCODE_NATIVE:
		/*
		 * check endianness, in case we are unpacking
		 * from a file
		 */
		if (nvl_endian != host_endian)
			return (ENOTSUP);
		err = nvs_native(&nvs, nvl, buf, buflen);
		break;
	case NV_ENCODE_XDR:
		err = nvs_xdr(&nvs, nvl, buf, buflen);
		break;
	default:
		err = ENOTSUP;
		break;
	}

	return (err);
}