#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t sp_digest_bitlen; } ;
typedef  TYPE_1__ skein_param_t ;
struct TYPE_5__ {int cm_param_len; int cm_type; int /*<<< orphan*/ * cm_param; } ;
typedef  TYPE_2__ crypto_mechanism_t ;

/* Variables and functions */
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
#define  SKEIN1024_MECH_INFO_TYPE 130 
#define  SKEIN_256_MECH_INFO_TYPE 129 
#define  SKEIN_512_MECH_INFO_TYPE 128 

__attribute__((used)) static int
skein_get_digest_bitlen(const crypto_mechanism_t *mechanism, size_t *result)
{
	if (mechanism->cm_param != NULL) {
		/*LINTED(E_BAD_PTR_CAST_ALIGN)*/
		skein_param_t	*param = (skein_param_t *)mechanism->cm_param;

		if (mechanism->cm_param_len != sizeof (*param) ||
		    param->sp_digest_bitlen == 0) {
			return (CRYPTO_MECHANISM_PARAM_INVALID);
		}
		*result = param->sp_digest_bitlen;
	} else {
		switch (mechanism->cm_type) {
		case SKEIN_256_MECH_INFO_TYPE:
			*result = 256;
			break;
		case SKEIN_512_MECH_INFO_TYPE:
			*result = 512;
			break;
		case SKEIN1024_MECH_INFO_TYPE:
			*result = 1024;
			break;
		default:
			return (CRYPTO_MECHANISM_INVALID);
		}
	}
	return (CRYPTO_SUCCESS);
}