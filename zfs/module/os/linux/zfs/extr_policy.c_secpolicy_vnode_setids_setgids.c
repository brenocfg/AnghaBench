#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gid_t ;
struct TYPE_6__ {int /*<<< orphan*/  user_ns; } ;
typedef  TYPE_1__ cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int EPERM ; 
 int /*<<< orphan*/  SGID_TO_KGID (scalar_t__) ; 
 scalar_t__ crgetfsgid (TYPE_1__ const*) ; 
 int /*<<< orphan*/  groupmember (scalar_t__,TYPE_1__ const*) ; 
 int /*<<< orphan*/  kgid_has_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int priv_policy_user (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
secpolicy_vnode_setids_setgids(const cred_t *cr, gid_t gid)
{
#if defined(CONFIG_USER_NS)
	if (!kgid_has_mapping(cr->user_ns, SGID_TO_KGID(gid)))
		return (EPERM);
#endif
	if (crgetfsgid(cr) != gid && !groupmember(gid, cr))
		return (priv_policy_user(cr, CAP_FSETID, B_FALSE, EPERM));

	return (0);
}