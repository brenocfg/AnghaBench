#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {int info; int size; int /*<<< orphan*/  name; scalar_t__ sib; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int /*<<< orphan*/  CTInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_SUBTYPE ; 
 int CTF_UNION ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctype_isbitfield (int) ; 
 scalar_t__ ctype_isfield (int) ; 
 scalar_t__ ctype_isxattrib (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gco2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_bf_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_tab_getint (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cconv_substruct_tab(CTState *cts, CType *d, uint8_t *dp,
				GCtab *t, int32_t *ip, CTInfo flags)
{
  CTypeID id = d->sib;
  while (id) {
    CType *df = ctype_get(cts, id);
    id = df->sib;
    if (ctype_isfield(df->info) || ctype_isbitfield(df->info)) {
      TValue *tv;
      int32_t i = *ip, iz = i;
      if (!gcref(df->name)) continue;  /* Ignore unnamed fields. */
      if (i >= 0) {
      retry:
	tv = (TValue *)lj_tab_getint(t, i);
	if (!tv || tvisnil(tv)) {
	  if (i == 0) { i = 1; goto retry; }  /* 1-based tables. */
	  if (iz == 0) { *ip = i = -1; goto tryname; }  /* Init named fields. */
	  break;  /* Stop at first nil. */
	}
	*ip = i + 1;
      } else {
      tryname:
	tv = (TValue *)lj_tab_getstr(t, gco2str(gcref(df->name)));
	if (!tv || tvisnil(tv)) continue;
      }
      if (ctype_isfield(df->info))
	lj_cconv_ct_tv(cts, ctype_rawchild(cts, df), dp+df->size, tv, flags);
      else
	lj_cconv_bf_tv(cts, df, dp+df->size, tv);
      if ((d->info & CTF_UNION)) break;
    } else if (ctype_isxattrib(df->info, CTA_SUBTYPE)) {
      cconv_substruct_tab(cts, ctype_rawchild(cts, df),
			  dp+df->size, t, ip, flags);
    }  /* Ignore all other entries in the chain. */
  }
}