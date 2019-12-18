#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ cTValue ;
struct TYPE_11__ {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  int /*<<< orphan*/  MSize ;

/* Variables and functions */
 int /*<<< orphan*/  STRFMT_G14 ; 
 int /*<<< orphan*/  intV (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_buf_tmp_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_strfmt_putfnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_strfmt_putint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* sbufB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuflen (int /*<<< orphan*/ *) ; 
 TYPE_6__* strV (TYPE_1__*) ; 
 char const* strVdata (TYPE_1__*) ; 
 scalar_t__ tvisint (TYPE_1__*) ; 
 scalar_t__ tvisnum (TYPE_1__*) ; 
 scalar_t__ tvisstr (TYPE_1__*) ; 

const char *lj_strfmt_wstrnum(lua_State *L, cTValue *o, MSize *lenp)
{
  SBuf *sb;
  if (tvisstr(o)) {
    *lenp = strV(o)->len;
    return strVdata(o);
  } else if (tvisint(o)) {
    sb = lj_strfmt_putint(lj_buf_tmp_(L), intV(o));
  } else if (tvisnum(o)) {
    sb = lj_strfmt_putfnum(lj_buf_tmp_(L), STRFMT_G14, o->n);
  } else {
    return NULL;
  }
  *lenp = sbuflen(sb);
  return sbufB(sb);
}