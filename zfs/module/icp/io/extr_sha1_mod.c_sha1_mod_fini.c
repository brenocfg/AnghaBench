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
 int EBUSY ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int) ; 
 int crypto_unregister_provider (scalar_t__) ; 
 int mod_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 
 scalar_t__ sha1_prov_handle ; 

int
sha1_mod_fini(void)
{
	int ret;

	if (sha1_prov_handle != 0) {
		if ((ret = crypto_unregister_provider(sha1_prov_handle)) !=
		    CRYPTO_SUCCESS) {
			cmn_err(CE_WARN,
			    "sha1 _fini: crypto_unregister_provider() "
			    "failed (0x%x)", ret);
			return (EBUSY);
		}
		sha1_prov_handle = 0;
	}

	return (mod_remove(&modlinkage));
}