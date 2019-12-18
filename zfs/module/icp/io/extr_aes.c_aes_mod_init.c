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

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  aes_impl_init () ; 
 int /*<<< orphan*/  aes_prov_handle ; 
 int /*<<< orphan*/  aes_prov_info ; 
 scalar_t__ crypto_register_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcm_impl_init () ; 
 int mod_install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 

int
aes_mod_init(void)
{
	int ret;

	/* Determine the fastest available implementation. */
	aes_impl_init();
	gcm_impl_init();

	if ((ret = mod_install(&modlinkage)) != 0)
		return (ret);

	/* Register with KCF.  If the registration fails, remove the module. */
	if (crypto_register_provider(&aes_prov_info, &aes_prov_handle)) {
		(void) mod_remove(&modlinkage);
		return (EACCES);
	}

	return (0);
}