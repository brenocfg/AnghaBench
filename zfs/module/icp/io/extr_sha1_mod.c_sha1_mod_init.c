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
 int /*<<< orphan*/  CE_WARN ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int) ; 
 int crypto_register_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mod_install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 
 int /*<<< orphan*/  sha1_prov_handle ; 
 int /*<<< orphan*/  sha1_prov_info ; 

int
sha1_mod_init(void)
{
	int ret;

	if ((ret = mod_install(&modlinkage)) != 0)
		return (ret);

	/*
	 * Register with KCF. If the registration fails, log an
	 * error but do not uninstall the module, since the functionality
	 * provided by misc/sha1 should still be available.
	 */
	if ((ret = crypto_register_provider(&sha1_prov_info,
	    &sha1_prov_handle)) != CRYPTO_SUCCESS)
		cmn_err(CE_WARN, "sha1 _init: "
		    "crypto_register_provider() failed (0x%x)", ret);

	return (0);
}