#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_share_impl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {char* shareopts; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 TYPE_1__* FSINFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SA_NO_MEMORY ; 
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  smb_disable_share (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_enable_share (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_fstype ; 
 scalar_t__ smb_is_share_active (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
smb_update_shareopts(sa_share_impl_t impl_share, const char *resource,
    const char *shareopts)
{
	char *shareopts_dup;
	boolean_t needs_reshare = B_FALSE;
	char *old_shareopts;

	if (!impl_share)
		return (SA_SYSTEM_ERR);

	FSINFO(impl_share, smb_fstype)->active =
	    smb_is_share_active(impl_share);

	old_shareopts = FSINFO(impl_share, smb_fstype)->shareopts;

	if (FSINFO(impl_share, smb_fstype)->active && old_shareopts != NULL &&
	    strcmp(old_shareopts, shareopts) != 0) {
		needs_reshare = B_TRUE;
		smb_disable_share(impl_share);
	}

	shareopts_dup = strdup(shareopts);

	if (shareopts_dup == NULL)
		return (SA_NO_MEMORY);

	if (old_shareopts != NULL)
		free(old_shareopts);

	FSINFO(impl_share, smb_fstype)->shareopts = shareopts_dup;

	if (needs_reshare)
		smb_enable_share(impl_share);

	return (SA_OK);
}