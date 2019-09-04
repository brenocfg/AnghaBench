#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* p; } ;
struct TYPE_10__ {scalar_t__ base; } ;
struct TYPE_11__ {TYPE_3__ l; } ;
struct TYPE_12__ {scalar_t__ func; TYPE_4__ u; } ;
struct TYPE_9__ {TYPE_1__* sp; } ;
struct TYPE_8__ {int numparams; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_5__ CallInfo ;

/* Variables and functions */
 int cast_int (scalar_t__) ; 
 TYPE_7__* clLvalue (scalar_t__) ; 

__attribute__((used)) static const char *findvararg (CallInfo *ci, int n, StkId *pos) {
  int nparams = clLvalue(ci->func)->p->sp->numparams;
  if (n >= cast_int(ci->u.l.base - ci->func) - nparams)
    return NULL;  /* no such vararg */
  else {
    *pos = ci->func + nparams + n;
    return "(*vararg)";  /* generic name for any vararg */
  }
}