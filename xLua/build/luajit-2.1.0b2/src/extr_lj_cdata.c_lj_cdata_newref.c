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
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CTINFO_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_cdata_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GCcdata *lj_cdata_newref(CTState *cts, const void *p, CTypeID id)
{
  CTypeID refid = lj_ctype_intern(cts, CTINFO_REF(id), CTSIZE_PTR);
  GCcdata *cd = lj_cdata_new(cts, refid, CTSIZE_PTR);
  *(const void **)cdataptr(cd) = p;
  return cd;
}