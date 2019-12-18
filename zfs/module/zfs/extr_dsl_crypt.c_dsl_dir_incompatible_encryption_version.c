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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 scalar_t__ ZIO_CRYPT_KEY_CURRENT_VERSION ; 
 int dsl_dir_get_encryption_version (int /*<<< orphan*/ *,scalar_t__*) ; 

boolean_t
dsl_dir_incompatible_encryption_version(dsl_dir_t *dd)
{
	int ret;
	uint64_t version = 0;

	ret = dsl_dir_get_encryption_version(dd, &version);
	if (ret != 0)
		return (B_FALSE);

	return (version != ZIO_CRYPT_KEY_CURRENT_VERSION);
}