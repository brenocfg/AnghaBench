#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ lua_Number ;
typedef  int int32_t ;
struct TYPE_11__ {int lo; int hi; } ;
struct TYPE_12__ {TYPE_1__ u32; } ;
typedef  TYPE_2__ cTValue ;
struct TYPE_14__ {int /*<<< orphan*/  sb; } ;
struct TYPE_13__ {int sizekn; int /*<<< orphan*/  k; } ;
typedef  int MSize ;
typedef  TYPE_3__ GCproto ;
typedef  TYPE_4__ BCWriteCtx ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_DUALNUM ; 
 int /*<<< orphan*/  TValue ; 
 int intV (TYPE_2__*) ; 
 char* lj_buf_more (int /*<<< orphan*/ *,int) ; 
 int lj_num2int (scalar_t__) ; 
 char* lj_strfmt_wuleb128 (char*,int) ; 
 TYPE_2__* mref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ numV (TYPE_2__*) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ tvisint (TYPE_2__*) ; 

__attribute__((used)) static void bcwrite_knum(BCWriteCtx *ctx, GCproto *pt)
{
  MSize i, sizekn = pt->sizekn;
  cTValue *o = mref(pt->k, TValue);
  char *p = lj_buf_more(&ctx->sb, 10*sizekn);
  for (i = 0; i < sizekn; i++, o++) {
    int32_t k;
    if (tvisint(o)) {
      k = intV(o);
      goto save_int;
    } else {
      /* Write a 33 bit ULEB128 for the int (lsb=0) or loword (lsb=1). */
      if (!LJ_DUALNUM) {  /* Narrow number constants to integers. */
	lua_Number num = numV(o);
	k = lj_num2int(num);
	if (num == (lua_Number)k) {  /* -0 is never a constant. */
	save_int:
	  p = lj_strfmt_wuleb128(p, 2*(uint32_t)k | ((uint32_t)k&0x80000000u));
	  if (k < 0)
	    p[-1] = (p[-1] & 7) | ((k>>27) & 0x18);
	  continue;
	}
      }
      p = lj_strfmt_wuleb128(p, 1+(2*o->u32.lo | (o->u32.lo & 0x80000000u)));
      if (o->u32.lo >= 0x80000000u)
	p[-1] = (p[-1] & 7) | ((o->u32.lo>>27) & 0x18);
      p = lj_strfmt_wuleb128(p, o->u32.hi);
    }
  }
  setsbufP(&ctx->sb, p);
}