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
struct TYPE_4__ {int /*<<< orphan*/ * user_ns; } ;
typedef  TYPE_1__ cred_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int priv_policy_ns (TYPE_1__ const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
priv_policy_user(const cred_t *cr, int capability, boolean_t all, int err)
{
	/*
	 * All priv_policy_user checks are preceded by kuid/kgid_has_mapping()
	 * checks. If we cannot do them, we shouldn't be using ns_capable()
	 * since we don't know whether the affected files are valid in our
	 * namespace.
	 */
#if defined(CONFIG_USER_NS)
	return (priv_policy_ns(cr, capability, all, err, cr->user_ns));
#else
	return (priv_policy_ns(cr, capability, all, err, NULL));
#endif
}