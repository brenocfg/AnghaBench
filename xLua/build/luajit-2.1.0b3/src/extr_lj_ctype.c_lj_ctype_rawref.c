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
struct TYPE_6__ {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 TYPE_1__* ctype_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isattrib (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isref (int /*<<< orphan*/ ) ; 

CType *lj_ctype_rawref(CTState *cts, CTypeID id)
{
  CType *ct = ctype_get(cts, id);
  while (ctype_isattrib(ct->info) || ctype_isref(ct->info))
    ct = ctype_child(cts, ct);
  return ct;
}