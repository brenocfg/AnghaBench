#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nvs_op; scalar_t__ nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_6__ {size_t n_curr; size_t n_end; } ;
typedef  TYPE_2__ nvs_native_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 int /*<<< orphan*/  bcopy (size_t,size_t*,int) ; 
 int nvs_native_nvp_op (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvs_native_nvpair(nvstream_t *nvs, nvpair_t *nvp, size_t *size)
{
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
		return (nvs_native_nvp_op(nvs, nvp));

	case NVS_OP_DECODE: {
		nvs_native_t *native = (nvs_native_t *)nvs->nvs_private;
		int32_t decode_len;

		/* try to read the size value from the stream */
		if (native->n_curr + sizeof (int32_t) > native->n_end)
			return (EFAULT);
		bcopy(native->n_curr, &decode_len, sizeof (int32_t));

		/* sanity check the size value */
		if (decode_len < 0 ||
		    decode_len > native->n_end - native->n_curr)
			return (EFAULT);

		*size = decode_len;

		/*
		 * If at the end of the stream then move the cursor
		 * forward, otherwise nvpair_native_op() will read
		 * the entire nvpair at the same cursor position.
		 */
		if (*size == 0)
			native->n_curr += sizeof (int32_t);
		break;
	}

	default:
		return (EINVAL);
	}

	return (0);
}