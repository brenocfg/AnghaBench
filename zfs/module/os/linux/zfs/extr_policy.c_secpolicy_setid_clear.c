#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int va_mode; int va_mask; scalar_t__ va_uid; } ;
typedef  TYPE_1__ vattr_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int AT_MODE ; 
 int AT_UID ; 
 int S_ISGID ; 
 int S_ISUID ; 
 scalar_t__ secpolicy_vnode_setid_retain (int /*<<< orphan*/ *,int) ; 

void
secpolicy_setid_clear(vattr_t *vap, cred_t *cr)
{
	if ((vap->va_mode & (S_ISUID | S_ISGID)) != 0 &&
	    secpolicy_vnode_setid_retain(cr,
	    (vap->va_mode & S_ISUID) != 0 &&
	    (vap->va_mask & AT_UID) != 0 && vap->va_uid == 0) != 0) {
		vap->va_mask |= AT_MODE;
		vap->va_mode &= ~(S_ISUID|S_ISGID);
	}
}