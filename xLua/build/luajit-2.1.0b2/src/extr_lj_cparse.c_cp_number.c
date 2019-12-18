#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ u32; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {char c; int mode; TYPE_1__ val; int /*<<< orphan*/  sb; } ;
struct TYPE_10__ {scalar_t__ i; } ;
typedef  TYPE_2__ TValue ;
typedef  scalar_t__ StrScanFmt ;
typedef  int /*<<< orphan*/  CPToken ;
typedef  TYPE_3__ CPState ;

/* Variables and functions */
 int CPARSE_MODE_SKIP ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int /*<<< orphan*/  CTID_UINT32 ; 
 int /*<<< orphan*/  CTOK_INTEGER ; 
 int /*<<< orphan*/  LJ_ERR_XNUMBER ; 
 scalar_t__ STRSCAN_INT ; 
 int /*<<< orphan*/  STRSCAN_OPT_C ; 
 scalar_t__ STRSCAN_U32 ; 
 int /*<<< orphan*/  cp_errmsg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_get (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_save (TYPE_3__*,char) ; 
 scalar_t__ lj_char_isident (int /*<<< orphan*/ ) ; 
 scalar_t__ lj_strscan_scan (int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbufB (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CPToken cp_number(CPState *cp)
{
  StrScanFmt fmt;
  TValue o;
  do { cp_save(cp, cp->c); } while (lj_char_isident(cp_get(cp)));
  cp_save(cp, '\0');
  fmt = lj_strscan_scan((const uint8_t *)sbufB(&cp->sb), &o, STRSCAN_OPT_C);
  if (fmt == STRSCAN_INT) cp->val.id = CTID_INT32;
  else if (fmt == STRSCAN_U32) cp->val.id = CTID_UINT32;
  else if (!(cp->mode & CPARSE_MODE_SKIP))
    cp_errmsg(cp, CTOK_INTEGER, LJ_ERR_XNUMBER);
  cp->val.u32 = (uint32_t)o.i;
  return CTOK_INTEGER;
}