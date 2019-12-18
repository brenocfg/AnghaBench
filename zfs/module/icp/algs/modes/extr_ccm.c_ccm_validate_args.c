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
typedef  int uint8_t ;
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {size_t ulMACSize; size_t ulNonceSize; size_t ulDataSize; } ;
typedef  TYPE_1__ CK_AES_CCM_PARAMS ;

/* Variables and functions */
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 unsigned long long ULONG_MAX ; 

int
ccm_validate_args(CK_AES_CCM_PARAMS *ccm_param, boolean_t is_encrypt_init)
{
	size_t macSize, nonceSize;
	uint8_t q;
	uint64_t maxValue;

	/*
	 * Check the length of the MAC.  The only valid
	 * lengths for the MAC are: 4, 6, 8, 10, 12, 14, 16
	 */
	macSize = ccm_param->ulMACSize;
	if ((macSize < 4) || (macSize > 16) || ((macSize % 2) != 0)) {
		return (CRYPTO_MECHANISM_PARAM_INVALID);
	}

	/* Check the nonce length.  Valid values are 7, 8, 9, 10, 11, 12, 13 */
	nonceSize = ccm_param->ulNonceSize;
	if ((nonceSize < 7) || (nonceSize > 13)) {
		return (CRYPTO_MECHANISM_PARAM_INVALID);
	}

	/* q is the length of the field storing the length, in bytes */
	q = (uint8_t)((15 - nonceSize) & 0xFF);


	/*
	 * If it is decrypt, need to make sure size of ciphertext is at least
	 * bigger than MAC len
	 */
	if ((!is_encrypt_init) && (ccm_param->ulDataSize < macSize)) {
		return (CRYPTO_MECHANISM_PARAM_INVALID);
	}

	/*
	 * Check to make sure the length of the payload is within the
	 * range of values allowed by q
	 */
	if (q < 8) {
		maxValue = (1ULL << (q * 8)) - 1;
	} else {
		maxValue = ULONG_MAX;
	}

	if (ccm_param->ulDataSize > maxValue) {
		return (CRYPTO_MECHANISM_PARAM_INVALID);
	}
	return (CRYPTO_SUCCESS);
}