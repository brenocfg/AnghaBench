#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  s; } ;
struct TYPE_14__ {TYPE_6__* cap; } ;
struct TYPE_11__ {int /*<<< orphan*/  e; int /*<<< orphan*/  s; } ;
struct TYPE_12__ {TYPE_1__ s; TYPE_6__* cp; } ;
struct TYPE_13__ {int isstring; TYPE_2__ u; } ;
typedef  TYPE_3__ StrAux ;
typedef  TYPE_4__ CapState ;

/* Variables and functions */
 scalar_t__ Csimple ; 
 int MAXSTRCAPS ; 
 scalar_t__ captype (TYPE_6__*) ; 
 int /*<<< orphan*/  closeaddr (TYPE_6__*) ; 
 int /*<<< orphan*/  isclosecap (TYPE_6__*) ; 
 int /*<<< orphan*/  isfullcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextcap (TYPE_4__*) ; 

__attribute__((used)) static int getstrcaps (CapState *cs, StrAux *cps, int n) {
  int k = n++;
  cps[k].isstring = 1;  /* get string value */
  cps[k].u.s.s = cs->cap->s;  /* starts here */
  if (!isfullcap(cs->cap++)) {  /* nested captures? */
    while (!isclosecap(cs->cap)) {  /* traverse them */
      if (n >= MAXSTRCAPS)  /* too many captures? */
        nextcap(cs);  /* skip extra captures (will not need them) */
      else if (captype(cs->cap) == Csimple)  /* string? */
        n = getstrcaps(cs, cps, n);  /* put info. into array */
      else {
        cps[n].isstring = 0;  /* not a string */
        cps[n].u.cp = cs->cap;  /* keep original capture */
        nextcap(cs);
        n++;
      }
    }
    cs->cap++;  /* skip close */
  }
  cps[k].u.s.e = closeaddr(cs->cap - 1);  /* ends here */
  return n;
}