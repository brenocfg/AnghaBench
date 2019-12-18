#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ mod_hash_val_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;
typedef  scalar_t__ crypto_mech_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CRYPTO_MECH_INVALID ; 
 int /*<<< orphan*/  kcf_mech_hash ; 
 scalar_t__ mod_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static crypto_mech_type_t
kcf_mech_hash_find(char *mechname)
{
	mod_hash_val_t hv;
	crypto_mech_type_t mt;

	mt = CRYPTO_MECH_INVALID;
	if (mod_hash_find(kcf_mech_hash, (mod_hash_key_t)mechname, &hv) == 0) {
		mt = *(crypto_mech_type_t *)hv;
		ASSERT(mt != CRYPTO_MECH_INVALID);
	}

	return (mt);
}