#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xdr_bytesrec {int /*<<< orphan*/  xc_num_avail; } ;
struct TYPE_9__ {int nvs_op; int /*<<< orphan*/ * nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_10__ {size_t nvp_size; } ;
typedef  TYPE_2__ nvpair_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 size_t NVS_XDR_MAX_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDR_GET_BYTES_AVAIL ; 
 int nvs_xdr_nvp_op (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nvs_xdr_nvp_size (TYPE_1__*,TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  xdr_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xdr_bytesrec*) ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
nvs_xdr_nvpair(nvstream_t *nvs, nvpair_t *nvp, size_t *size)
{
	XDR 	*xdr = nvs->nvs_private;
	int32_t	encode_len, decode_len;

	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE: {
		size_t nvsize;

		if (nvs_xdr_nvp_size(nvs, nvp, &nvsize) != 0)
			return (EFAULT);

		decode_len = nvp->nvp_size;
		encode_len = nvsize;
		if (!xdr_int(xdr, &encode_len) || !xdr_int(xdr, &decode_len))
			return (EFAULT);

		return (nvs_xdr_nvp_op(nvs, nvp));
	}
	case NVS_OP_DECODE: {
		struct xdr_bytesrec bytesrec;

		/* get the encode and decode size */
		if (!xdr_int(xdr, &encode_len) || !xdr_int(xdr, &decode_len))
			return (EFAULT);
		*size = decode_len;

		/* are we at the end of the stream? */
		if (*size == 0)
			return (0);

		/* sanity check the size parameter */
		if (!xdr_control(xdr, XDR_GET_BYTES_AVAIL, &bytesrec))
			return (EFAULT);

		if (*size > NVS_XDR_MAX_LEN(bytesrec.xc_num_avail))
			return (EFAULT);
		break;
	}

	default:
		return (EINVAL);
	}
	return (0);
}