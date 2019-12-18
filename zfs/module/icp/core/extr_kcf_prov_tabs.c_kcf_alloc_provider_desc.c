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
typedef  int uint_t ;
struct TYPE_5__ {char* pd_description; int pd_mech_list_count; int /*<<< orphan*/  pd_remove_cv; int /*<<< orphan*/  pd_resume_cv; int /*<<< orphan*/  pd_lock; int /*<<< orphan*/  pd_state; int /*<<< orphan*/  pd_prov_id; int /*<<< orphan*/ ** pd_mech_indx; void* pd_mechanisms; void* pd_ops_vector; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
struct TYPE_6__ {int pi_mech_list_count; scalar_t__ pi_provider_type; scalar_t__ pi_interface_version; int /*<<< orphan*/ * pi_ops_vector; } ;
typedef  TYPE_2__ crypto_provider_info_t ;
typedef  int /*<<< orphan*/  crypto_ops_t ;
typedef  int /*<<< orphan*/  crypto_mech_info_t ;

/* Variables and functions */
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int CRYPTO_PROVIDER_DESCR_MAX_LEN ; 
 scalar_t__ CRYPTO_SPI_VERSION_2 ; 
 scalar_t__ CRYPTO_SPI_VERSION_3 ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  KCF_INVALID_INDX ; 
 int KCF_MAXMECHTAB ; 
 int KCF_OPS_CLASSSIZE ; 
 int /*<<< orphan*/  KCF_PROVID_INVALID ; 
 int /*<<< orphan*/  KCF_PROV_ALLOCATED ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  allocate_ops_v1 (int /*<<< orphan*/ *,void*,int*) ; 
 int /*<<< orphan*/  allocate_ops_v2 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  allocate_ops_v3 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kcf_provider_desc_t *
kcf_alloc_provider_desc(crypto_provider_info_t *info)
{
	int i, j;
	kcf_provider_desc_t *desc;
	uint_t mech_list_count = info->pi_mech_list_count;
	crypto_ops_t *src_ops = info->pi_ops_vector;

	desc = kmem_zalloc(sizeof (kcf_provider_desc_t), KM_SLEEP);

	/*
	 * pd_description serves two purposes
	 * - Appears as a blank padded PKCS#11 style string, that will be
	 *   returned to applications in CK_SLOT_INFO.slotDescription.
	 *   This means that we should not have a null character in the
	 *   first CRYPTO_PROVIDER_DESCR_MAX_LEN bytes.
	 * - Appears as a null-terminated string that can be used by
	 *   other kcf routines.
	 *
	 * So, we allocate enough room for one extra null terminator
	 * which keeps every one happy.
	 */
	desc->pd_description = kmem_alloc(CRYPTO_PROVIDER_DESCR_MAX_LEN + 1,
	    KM_SLEEP);
	(void) memset(desc->pd_description, ' ',
	    CRYPTO_PROVIDER_DESCR_MAX_LEN);
	desc->pd_description[CRYPTO_PROVIDER_DESCR_MAX_LEN] = '\0';

	/*
	 * Since the framework does not require the ops vector specified
	 * by the providers during registration to be persistent,
	 * KCF needs to allocate storage where copies of the ops
	 * vectors are copied.
	 */
	desc->pd_ops_vector = kmem_zalloc(sizeof (crypto_ops_t), KM_SLEEP);

	if (info->pi_provider_type != CRYPTO_LOGICAL_PROVIDER) {
		allocate_ops_v1(src_ops, desc->pd_ops_vector, &mech_list_count);
		if (info->pi_interface_version >= CRYPTO_SPI_VERSION_2)
			allocate_ops_v2(src_ops, desc->pd_ops_vector);
		if (info->pi_interface_version == CRYPTO_SPI_VERSION_3)
			allocate_ops_v3(src_ops, desc->pd_ops_vector);
	}

	desc->pd_mech_list_count = mech_list_count;
	desc->pd_mechanisms = kmem_zalloc(sizeof (crypto_mech_info_t) *
	    mech_list_count, KM_SLEEP);
	for (i = 0; i < KCF_OPS_CLASSSIZE; i++)
		for (j = 0; j < KCF_MAXMECHTAB; j++)
			desc->pd_mech_indx[i][j] = KCF_INVALID_INDX;

	desc->pd_prov_id = KCF_PROVID_INVALID;
	desc->pd_state = KCF_PROV_ALLOCATED;

	mutex_init(&desc->pd_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&desc->pd_resume_cv, NULL, CV_DEFAULT, NULL);
	cv_init(&desc->pd_remove_cv, NULL, CV_DEFAULT, NULL);

	return (desc);
}