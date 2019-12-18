#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cp_crypt; } ;
typedef  TYPE_1__ dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_CRYPT_INHERIT ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 int dmu_objset_create_crypt_check (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spa_create_check_encryption_params(dsl_crypto_params_t *dcp,
    boolean_t has_encryption)
{
	if (dcp->cp_crypt != ZIO_CRYPT_OFF &&
	    dcp->cp_crypt != ZIO_CRYPT_INHERIT &&
	    !has_encryption)
		return (SET_ERROR(ENOTSUP));

	return (dmu_objset_create_crypt_check(NULL, dcp, NULL));
}