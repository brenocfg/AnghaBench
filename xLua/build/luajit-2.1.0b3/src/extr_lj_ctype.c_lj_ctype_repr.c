#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_11__ {int ok; int /*<<< orphan*/ * pb; int /*<<< orphan*/ * pe; scalar_t__ needsp; int /*<<< orphan*/ * L; int /*<<< orphan*/  cts; int /*<<< orphan*/ * buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ GCstr ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CTRepr ;

/* Variables and functions */
 int CTREPR_MAX ; 
 int /*<<< orphan*/ * G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  ctype_ctsG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctype_prepstr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_repr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lj_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* lj_str_newlit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdata (TYPE_1__*) ; 

GCstr *lj_ctype_repr(lua_State *L, CTypeID id, GCstr *name)
{
  global_State *g = G(L);
  CTRepr ctr;
  ctr.pb = ctr.pe = &ctr.buf[CTREPR_MAX/2];
  ctr.cts = ctype_ctsG(g);
  ctr.L = L;
  ctr.ok = 1;
  ctr.needsp = 0;
  if (name) ctype_prepstr(&ctr, strdata(name), name->len);
  ctype_repr(&ctr, id);
  if (LJ_UNLIKELY(!ctr.ok)) return lj_str_newlit(L, "?");
  return lj_str_new(L, ctr.pb, ctr.pe - ctr.pb);
}