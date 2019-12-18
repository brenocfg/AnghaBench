#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_provider_handle_t ;
struct TYPE_5__ {int cm_param_len; char* cm_param; int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_1__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
typedef  int /*<<< orphan*/  crypto_data_t ;
typedef  int /*<<< orphan*/  CK_AES_GCM_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  AES_GCM_MECH_INFO_TYPE ; 
 int CRYPTO_SUCCESS ; 
 int aes_decrypt_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_crypto_data ; 
 int process_gmac_mech (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aes_mac_verify_atomic(crypto_provider_handle_t provider,
    crypto_session_id_t session_id, crypto_mechanism_t *mechanism,
    crypto_key_t *key, crypto_data_t *data, crypto_data_t *mac,
    crypto_spi_ctx_template_t template, crypto_req_handle_t req)
{
	CK_AES_GCM_PARAMS gcm_params;
	crypto_mechanism_t gcm_mech;
	int rv;

	if ((rv = process_gmac_mech(mechanism, data, &gcm_params))
	    != CRYPTO_SUCCESS)
		return (rv);

	gcm_mech.cm_type = AES_GCM_MECH_INFO_TYPE;
	gcm_mech.cm_param_len = sizeof (CK_AES_GCM_PARAMS);
	gcm_mech.cm_param = (char *)&gcm_params;

	return (aes_decrypt_atomic(provider, session_id, &gcm_mech,
	    key, mac, &null_crypto_data, template, req));
}