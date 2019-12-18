#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_9__ {int /*<<< orphan*/  strempty; } ;
struct TYPE_8__ {TYPE_3__* g; int /*<<< orphan*/  miscmap; } ;
struct TYPE_7__ {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  MMS ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 scalar_t__ ctype_cid (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_get (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ctype_isattrib (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_getinth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmname_str (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 

cTValue *lj_ctype_meta(CTState *cts, CTypeID id, MMS mm)
{
  CType *ct = ctype_get(cts, id);
  cTValue *tv;
  while (ctype_isattrib(ct->info) || ctype_isref(ct->info)) {
    id = ctype_cid(ct->info);
    ct = ctype_get(cts, id);
  }
  if (ctype_isptr(ct->info) &&
      ctype_isfunc(ctype_get(cts, ctype_cid(ct->info))->info))
    tv = lj_tab_getstr(cts->miscmap, &cts->g->strempty);
  else
    tv = lj_tab_getinth(cts->miscmap, -(int32_t)id);
  if (tv && tvistab(tv) &&
      (tv = lj_tab_getstr(tabV(tv), mmname_str(cts->g, mm))) && !tvisnil(tv))
    return tv;
  return NULL;
}