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
typedef  scalar_t__ uid_t ;
struct inode {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  user_ns; } ;
typedef  TYPE_1__ cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  CAP_DAC_OVERRIDE ; 
 int /*<<< orphan*/  CAP_DAC_READ_SEARCH ; 
 int EPERM ; 
 int /*<<< orphan*/  SUID_TO_KUID (scalar_t__) ; 
 scalar_t__ crgetfsuid (TYPE_1__ const*) ; 
 scalar_t__ inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  kuid_has_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ priv_policy_user (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
secpolicy_vnode_any_access(const cred_t *cr, struct inode *ip, uid_t owner)
{
	if (crgetfsuid(cr) == owner)
		return (0);

	if (inode_owner_or_capable(ip))
		return (0);

#if defined(CONFIG_USER_NS)
	if (!kuid_has_mapping(cr->user_ns, SUID_TO_KUID(owner)))
		return (EPERM);
#endif

	if (priv_policy_user(cr, CAP_DAC_OVERRIDE, B_FALSE, EPERM) == 0)
		return (0);

	if (priv_policy_user(cr, CAP_DAC_READ_SEARCH, B_FALSE, EPERM) == 0)
		return (0);

	return (EPERM);
}