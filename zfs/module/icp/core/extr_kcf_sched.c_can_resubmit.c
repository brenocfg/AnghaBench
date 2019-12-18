#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  cm_type; } ;
struct TYPE_20__ {TYPE_12__ vo_mech; int /*<<< orphan*/  vo_framework_mechtype; } ;
typedef  TYPE_2__ kcf_verify_ops_params_t ;
struct TYPE_21__ {TYPE_12__ so_mech; int /*<<< orphan*/  so_framework_mechtype; } ;
typedef  TYPE_3__ kcf_sign_ops_params_t ;
struct TYPE_24__ {TYPE_12__ md_decr_mech; int /*<<< orphan*/  md_framework_decr_mechtype; TYPE_12__ md_mac_mech; int /*<<< orphan*/  md_framework_mac_mechtype; } ;
struct TYPE_26__ {TYPE_12__ em_mac_mech; int /*<<< orphan*/  em_framework_mac_mechtype; TYPE_12__ em_encr_mech; int /*<<< orphan*/  em_framework_encr_mechtype; } ;
struct TYPE_16__ {TYPE_12__ dop_mech; int /*<<< orphan*/  dop_framework_mechtype; } ;
struct TYPE_25__ {TYPE_12__ eo_mech; int /*<<< orphan*/  eo_framework_mechtype; } ;
struct TYPE_23__ {TYPE_12__ mo_mech; int /*<<< orphan*/  mo_framework_mechtype; } ;
struct TYPE_27__ {TYPE_12__ do_mech; int /*<<< orphan*/  do_framework_mechtype; } ;
struct TYPE_19__ {TYPE_6__ mac_decrypt_params; TYPE_8__ encrypt_mac_params; TYPE_10__ decrypt_params; TYPE_7__ encrypt_params; TYPE_2__ verify_params; TYPE_3__ sign_params; TYPE_5__ mac_params; TYPE_9__ digest_params; } ;
struct TYPE_22__ {int rp_optype; int rp_opgrp; TYPE_1__ rp_u; } ;
typedef  TYPE_4__ kcf_req_params_t ;
typedef  int kcf_op_type_t ;
typedef  TYPE_5__ kcf_mac_ops_params_t ;
typedef  TYPE_6__ kcf_mac_decrypt_ops_params_t ;
typedef  TYPE_7__ kcf_encrypt_ops_params_t ;
typedef  TYPE_8__ kcf_encrypt_mac_ops_params_t ;
typedef  TYPE_9__ kcf_digest_ops_params_t ;
typedef  TYPE_10__ kcf_decrypt_ops_params_t ;
struct TYPE_17__ {TYPE_4__ an_params; } ;
typedef  TYPE_11__ kcf_areq_node_t ;
typedef  TYPE_12__ crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_func_group_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  CRYPTO_FG_DECRYPT ; 
 int /*<<< orphan*/  CRYPTO_FG_DECRYPT_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_DIGEST ; 
 int /*<<< orphan*/  CRYPTO_FG_DIGEST_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_ENCRYPT ; 
 int /*<<< orphan*/  CRYPTO_FG_ENCRYPT_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_ENCRYPT_MAC ; 
 int /*<<< orphan*/  CRYPTO_FG_ENCRYPT_MAC_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC_DECRYPT ; 
 int /*<<< orphan*/  CRYPTO_FG_MAC_DECRYPT_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_SIGN ; 
 int /*<<< orphan*/  CRYPTO_FG_SIGN_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_SIGN_RECOVER_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_VERIFY ; 
 int /*<<< orphan*/  CRYPTO_FG_VERIFY_ATOMIC ; 
 int /*<<< orphan*/  CRYPTO_FG_VERIFY_RECOVER_ATOMIC ; 
 scalar_t__ IS_ATOMIC_OP (int) ; 
 scalar_t__ IS_INIT_OP (int) ; 
#define  KCF_OG_DECRYPT 137 
#define  KCF_OG_DIGEST 136 
#define  KCF_OG_ENCRYPT 135 
#define  KCF_OG_ENCRYPT_MAC 134 
#define  KCF_OG_MAC 133 
#define  KCF_OG_MAC_DECRYPT 132 
#define  KCF_OG_SIGN 131 
#define  KCF_OG_VERIFY 130 
#define  KCF_OP_ATOMIC 129 
#define  KCF_OP_INIT 128 
 int KCF_OP_SIGN_RECOVER_ATOMIC ; 
 int KCF_OP_VERIFY_RECOVER_ATOMIC ; 

__attribute__((used)) static boolean_t
can_resubmit(kcf_areq_node_t *areq, crypto_mechanism_t **mech1,
    crypto_mechanism_t **mech2, crypto_func_group_t *fg)
{
	kcf_req_params_t *params;
	kcf_op_type_t optype;

	params = &areq->an_params;
	optype = params->rp_optype;

	if (!(IS_INIT_OP(optype) || IS_ATOMIC_OP(optype)))
		return (B_FALSE);

	switch (params->rp_opgrp) {
	case KCF_OG_DIGEST: {
		kcf_digest_ops_params_t *dops = &params->rp_u.digest_params;

		dops->do_mech.cm_type = dops->do_framework_mechtype;
		*mech1 = &dops->do_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_DIGEST :
		    CRYPTO_FG_DIGEST_ATOMIC;
		break;
	}

	case KCF_OG_MAC: {
		kcf_mac_ops_params_t *mops = &params->rp_u.mac_params;

		mops->mo_mech.cm_type = mops->mo_framework_mechtype;
		*mech1 = &mops->mo_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_MAC :
		    CRYPTO_FG_MAC_ATOMIC;
		break;
	}

	case KCF_OG_SIGN: {
		kcf_sign_ops_params_t *sops = &params->rp_u.sign_params;

		sops->so_mech.cm_type = sops->so_framework_mechtype;
		*mech1 = &sops->so_mech;
		switch (optype) {
		case KCF_OP_INIT:
			*fg = CRYPTO_FG_SIGN;
			break;
		case KCF_OP_ATOMIC:
			*fg = CRYPTO_FG_SIGN_ATOMIC;
			break;
		default:
			ASSERT(optype == KCF_OP_SIGN_RECOVER_ATOMIC);
			*fg = CRYPTO_FG_SIGN_RECOVER_ATOMIC;
		}
		break;
	}

	case KCF_OG_VERIFY: {
		kcf_verify_ops_params_t *vops = &params->rp_u.verify_params;

		vops->vo_mech.cm_type = vops->vo_framework_mechtype;
		*mech1 = &vops->vo_mech;
		switch (optype) {
		case KCF_OP_INIT:
			*fg = CRYPTO_FG_VERIFY;
			break;
		case KCF_OP_ATOMIC:
			*fg = CRYPTO_FG_VERIFY_ATOMIC;
			break;
		default:
			ASSERT(optype == KCF_OP_VERIFY_RECOVER_ATOMIC);
			*fg = CRYPTO_FG_VERIFY_RECOVER_ATOMIC;
		}
		break;
	}

	case KCF_OG_ENCRYPT: {
		kcf_encrypt_ops_params_t *eops = &params->rp_u.encrypt_params;

		eops->eo_mech.cm_type = eops->eo_framework_mechtype;
		*mech1 = &eops->eo_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_ENCRYPT :
		    CRYPTO_FG_ENCRYPT_ATOMIC;
		break;
	}

	case KCF_OG_DECRYPT: {
		kcf_decrypt_ops_params_t *dcrops = &params->rp_u.decrypt_params;

		dcrops->dop_mech.cm_type = dcrops->dop_framework_mechtype;
		*mech1 = &dcrops->dop_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_DECRYPT :
		    CRYPTO_FG_DECRYPT_ATOMIC;
		break;
	}

	case KCF_OG_ENCRYPT_MAC: {
		kcf_encrypt_mac_ops_params_t *eops =
		    &params->rp_u.encrypt_mac_params;

		eops->em_encr_mech.cm_type = eops->em_framework_encr_mechtype;
		*mech1 = &eops->em_encr_mech;
		eops->em_mac_mech.cm_type = eops->em_framework_mac_mechtype;
		*mech2 = &eops->em_mac_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_ENCRYPT_MAC :
		    CRYPTO_FG_ENCRYPT_MAC_ATOMIC;
		break;
	}

	case KCF_OG_MAC_DECRYPT: {
		kcf_mac_decrypt_ops_params_t *dops =
		    &params->rp_u.mac_decrypt_params;

		dops->md_mac_mech.cm_type = dops->md_framework_mac_mechtype;
		*mech1 = &dops->md_mac_mech;
		dops->md_decr_mech.cm_type = dops->md_framework_decr_mechtype;
		*mech2 = &dops->md_decr_mech;
		*fg = (optype == KCF_OP_INIT) ? CRYPTO_FG_MAC_DECRYPT :
		    CRYPTO_FG_MAC_DECRYPT_ATOMIC;
		break;
	}

	default:
		return (B_FALSE);
	}

	return (B_TRUE);
}