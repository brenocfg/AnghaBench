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
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  int /*<<< orphan*/  AliasRet ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_MAY ; 
 int /*<<< orphan*/  ALIAS_NO ; 
 int /*<<< orphan*/  aa_escape (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aa_findcnew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static AliasRet aa_cnew(jit_State *J, IRIns *refa, IRIns *refb)
{
  IRIns *cnewa = aa_findcnew(J, refa);
  IRIns *cnewb = aa_findcnew(J, refb);
  if (cnewa == cnewb)
    return ALIAS_MAY;  /* Same allocation or neither is an allocation. */
  if (cnewa && cnewb)
    return ALIAS_NO;  /* Two different allocations never alias. */
  if (cnewb) { cnewa = cnewb; refb = refa; }
  return aa_escape(J, cnewa, refb);
}