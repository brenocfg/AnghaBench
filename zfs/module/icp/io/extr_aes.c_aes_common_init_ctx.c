#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gcm_ctx_t ;
typedef  int /*<<< orphan*/  ctr_ctx_t ;
typedef  int /*<<< orphan*/  crypto_spi_ctx_template_t ;
struct TYPE_6__ {int cm_type; int cm_param_len; int /*<<< orphan*/ * cm_param; } ;
typedef  TYPE_1__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
typedef  int /*<<< orphan*/  ccm_ctx_t ;
typedef  int /*<<< orphan*/  cbc_ctx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int ac_flags; size_t ac_keysched_len; void* ac_keysched; } ;
typedef  TYPE_2__ aes_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  ulCounterBits; } ;
typedef  int /*<<< orphan*/  CK_AES_GMAC_PARAMS ;
typedef  int /*<<< orphan*/  CK_AES_GCM_PARAMS ;
typedef  TYPE_3__ CK_AES_CTR_PARAMS ;
typedef  int /*<<< orphan*/  CK_AES_CCM_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_LEN ; 
#define  AES_CBC_MECH_INFO_TYPE 133 
#define  AES_CCM_MECH_INFO_TYPE 132 
#define  AES_CTR_MECH_INFO_TYPE 131 
#define  AES_ECB_MECH_INFO_TYPE 130 
#define  AES_GCM_MECH_INFO_TYPE 129 
#define  AES_GMAC_MECH_INFO_TYPE 128 
 int CRYPTO_HOST_MEMORY ; 
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 int ECB_MODE ; 
 int PROVIDER_OWNS_KEY_SCHEDULE ; 
 void* aes_alloc_keysched (size_t*,int) ; 
 int /*<<< orphan*/  aes_copy_block ; 
 int /*<<< orphan*/  aes_copy_block64 ; 
 int /*<<< orphan*/  aes_encrypt_block ; 
 int /*<<< orphan*/  aes_xor_block ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 int cbc_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccm_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctr_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gcm_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gmac_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_keysched (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  kmem_free (void*,size_t) ; 

__attribute__((used)) static int
aes_common_init_ctx(aes_ctx_t *aes_ctx, crypto_spi_ctx_template_t *template,
    crypto_mechanism_t *mechanism, crypto_key_t *key, int kmflag,
    boolean_t is_encrypt_init)
{
	int rv = CRYPTO_SUCCESS;
	void *keysched;
	size_t size = 0;

	if (template == NULL) {
		if ((keysched = aes_alloc_keysched(&size, kmflag)) == NULL)
			return (CRYPTO_HOST_MEMORY);
		/*
		 * Initialize key schedule.
		 * Key length is stored in the key.
		 */
		if ((rv = init_keysched(key, keysched)) != CRYPTO_SUCCESS) {
			kmem_free(keysched, size);
			return (rv);
		}

		aes_ctx->ac_flags |= PROVIDER_OWNS_KEY_SCHEDULE;
		aes_ctx->ac_keysched_len = size;
	} else {
		keysched = template;
	}
	aes_ctx->ac_keysched = keysched;

	switch (mechanism->cm_type) {
	case AES_CBC_MECH_INFO_TYPE:
		rv = cbc_init_ctx((cbc_ctx_t *)aes_ctx, mechanism->cm_param,
		    mechanism->cm_param_len, AES_BLOCK_LEN, aes_copy_block64);
		break;
	case AES_CTR_MECH_INFO_TYPE: {
		CK_AES_CTR_PARAMS *pp;

		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (CK_AES_CTR_PARAMS)) {
			return (CRYPTO_MECHANISM_PARAM_INVALID);
		}
		pp = (CK_AES_CTR_PARAMS *)(void *)mechanism->cm_param;
		rv = ctr_init_ctx((ctr_ctx_t *)aes_ctx, pp->ulCounterBits,
		    pp->cb, aes_copy_block);
		break;
	}
	case AES_CCM_MECH_INFO_TYPE:
		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (CK_AES_CCM_PARAMS)) {
			return (CRYPTO_MECHANISM_PARAM_INVALID);
		}
		rv = ccm_init_ctx((ccm_ctx_t *)aes_ctx, mechanism->cm_param,
		    kmflag, is_encrypt_init, AES_BLOCK_LEN, aes_encrypt_block,
		    aes_xor_block);
		break;
	case AES_GCM_MECH_INFO_TYPE:
		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (CK_AES_GCM_PARAMS)) {
			return (CRYPTO_MECHANISM_PARAM_INVALID);
		}
		rv = gcm_init_ctx((gcm_ctx_t *)aes_ctx, mechanism->cm_param,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_copy_block,
		    aes_xor_block);
		break;
	case AES_GMAC_MECH_INFO_TYPE:
		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (CK_AES_GMAC_PARAMS)) {
			return (CRYPTO_MECHANISM_PARAM_INVALID);
		}
		rv = gmac_init_ctx((gcm_ctx_t *)aes_ctx, mechanism->cm_param,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_copy_block,
		    aes_xor_block);
		break;
	case AES_ECB_MECH_INFO_TYPE:
		aes_ctx->ac_flags |= ECB_MODE;
	}

	if (rv != CRYPTO_SUCCESS) {
		if (aes_ctx->ac_flags & PROVIDER_OWNS_KEY_SCHEDULE) {
			bzero(keysched, size);
			kmem_free(keysched, size);
		}
	}

	return (rv);
}