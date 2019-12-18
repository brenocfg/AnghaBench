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
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 int /*<<< orphan*/ * lj_strfmt_number (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstrV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCstr *argv2str(jit_State *J, TValue *o)
{
  if (LJ_LIKELY(tvisstr(o))) {
    return strV(o);
  } else {
    GCstr *s;
    if (!tvisnumber(o))
      lj_trace_err(J, LJ_TRERR_BADTYPE);
    s = lj_strfmt_number(J->L, o);
    setstrV(J->L, o, s);
    return s;
  }
}