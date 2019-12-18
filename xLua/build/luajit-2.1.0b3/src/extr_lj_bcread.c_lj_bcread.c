#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_16__ {int top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ int32_t ;
struct TYPE_17__ {scalar_t__ c; scalar_t__* p; scalar_t__* pe; int /*<<< orphan*/  sb; TYPE_1__* L; } ;
typedef  int MSize ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCproto ;

/* Variables and functions */
 scalar_t__ BCDUMP_HEAD1 ; 
 int /*<<< orphan*/  LJ_ERR_BCBAD ; 
 int /*<<< orphan*/  LJ_ERR_BCFMT ; 
 int /*<<< orphan*/  bcread_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcread_header (TYPE_2__*) ; 
 int /*<<< orphan*/  bcread_need (TYPE_2__*,int) ; 
 int bcread_oldtop (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bcread_savetop (TYPE_1__*,TYPE_2__*,int) ; 
 int bcread_uleb128 (TYPE_2__*) ; 
 int /*<<< orphan*/  bcread_want (TYPE_2__*,int) ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * lj_bcread_proto (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_buf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * protoV (int) ; 
 int /*<<< orphan*/  setprotoV (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

GCproto *lj_bcread(LexState *ls)
{
  lua_State *L = ls->L;
  lua_assert(ls->c == BCDUMP_HEAD1);
  bcread_savetop(L, ls, L->top);
  lj_buf_reset(&ls->sb);
  /* Check for a valid bytecode dump header. */
  if (!bcread_header(ls))
    bcread_error(ls, LJ_ERR_BCFMT);
  for (;;) {  /* Process all prototypes in the bytecode dump. */
    GCproto *pt;
    MSize len;
    const char *startp;
    /* Read length. */
    if (ls->p < ls->pe && ls->p[0] == 0) {  /* Shortcut EOF. */
      ls->p++;
      break;
    }
    bcread_want(ls, 5);
    len = bcread_uleb128(ls);
    if (!len) break;  /* EOF */
    bcread_need(ls, len);
    startp = ls->p;
    pt = lj_bcread_proto(ls);
    if (ls->p != startp + len)
      bcread_error(ls, LJ_ERR_BCBAD);
    setprotoV(L, L->top, pt);
    incr_top(L);
  }
  if ((int32_t)(2*(uint32_t)(ls->pe - ls->p)) > 0 ||
      L->top-1 != bcread_oldtop(L, ls))
    bcread_error(ls, LJ_ERR_BCBAD);
  /* Pop off last prototype. */
  L->top--;
  return protoV(L->top);
}