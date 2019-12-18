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
struct TYPE_3__ {int cm_type; size_t cm_param_len; int /*<<< orphan*/ * cm_param; } ;
typedef  TYPE_1__ crypto_mechanism_t ;
typedef  scalar_t__ boolean_t ;
typedef  void* alloc_fun ;
typedef  int /*<<< orphan*/  aes_ctx_t ;
typedef  int /*<<< orphan*/  CK_AES_GMAC_PARAMS ;
typedef  int /*<<< orphan*/  CK_AES_GCM_PARAMS ;
typedef  int /*<<< orphan*/  CK_AES_CTR_PARAMS ;
typedef  int /*<<< orphan*/  CK_AES_CCM_PARAMS ;

/* Variables and functions */
 size_t AES_BLOCK_LEN ; 
#define  AES_CBC_MECH_INFO_TYPE 133 
#define  AES_CCM_MECH_INFO_TYPE 132 
#define  AES_CTR_MECH_INFO_TYPE 131 
#define  AES_ECB_MECH_INFO_TYPE 130 
#define  AES_GCM_MECH_INFO_TYPE 129 
#define  AES_GMAC_MECH_INFO_TYPE 128 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 void* cbc_alloc_ctx (int) ; 
 void* ccm_alloc_ctx (int) ; 
 void* ctr_alloc_ctx (int) ; 
 void* ecb_alloc_ctx (int) ; 
 void* gcm_alloc_ctx (int) ; 
 void* gmac_alloc_ctx (int) ; 

__attribute__((used)) static int
aes_check_mech_param(crypto_mechanism_t *mechanism, aes_ctx_t **ctx, int kmflag)
{
	void *p = NULL;
	boolean_t param_required = B_TRUE;
	size_t param_len;
	void *(*alloc_fun)(int);
	int rv = CRYPTO_SUCCESS;

	switch (mechanism->cm_type) {
	case AES_ECB_MECH_INFO_TYPE:
		param_required = B_FALSE;
		alloc_fun = ecb_alloc_ctx;
		break;
	case AES_CBC_MECH_INFO_TYPE:
		param_len = AES_BLOCK_LEN;
		alloc_fun = cbc_alloc_ctx;
		break;
	case AES_CTR_MECH_INFO_TYPE:
		param_len = sizeof (CK_AES_CTR_PARAMS);
		alloc_fun = ctr_alloc_ctx;
		break;
	case AES_CCM_MECH_INFO_TYPE:
		param_len = sizeof (CK_AES_CCM_PARAMS);
		alloc_fun = ccm_alloc_ctx;
		break;
	case AES_GCM_MECH_INFO_TYPE:
		param_len = sizeof (CK_AES_GCM_PARAMS);
		alloc_fun = gcm_alloc_ctx;
		break;
	case AES_GMAC_MECH_INFO_TYPE:
		param_len = sizeof (CK_AES_GMAC_PARAMS);
		alloc_fun = gmac_alloc_ctx;
		break;
	default:
		rv = CRYPTO_MECHANISM_INVALID;
		return (rv);
	}
	if (param_required && mechanism->cm_param != NULL &&
	    mechanism->cm_param_len != param_len) {
		rv = CRYPTO_MECHANISM_PARAM_INVALID;
	}
	if (ctx != NULL) {
		p = (alloc_fun)(kmflag);
		*ctx = p;
	}
	return (rv);
}