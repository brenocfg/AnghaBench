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
struct TYPE_8__ {int info; int size; int /*<<< orphan*/  name; scalar_t__ sib; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int MSize ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_SUBTYPE ; 
 int CTF_UNION ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctype_isbitfield (int) ; 
 scalar_t__ ctype_isfield (int) ; 
 scalar_t__ ctype_isxattrib (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_bf_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cconv_substruct_init(CTState *cts, CType *d, uint8_t *dp,
				 TValue *o, MSize len, MSize *ip)
{
  CTypeID id = d->sib;
  while (id) {
    CType *df = ctype_get(cts, id);
    id = df->sib;
    if (ctype_isfield(df->info) || ctype_isbitfield(df->info)) {
      MSize i = *ip;
      if (!gcref(df->name)) continue;  /* Ignore unnamed fields. */
      if (i >= len) break;
      *ip = i + 1;
      if (ctype_isfield(df->info))
	lj_cconv_ct_tv(cts, ctype_rawchild(cts, df), dp+df->size, o + i, 0);
      else
	lj_cconv_bf_tv(cts, df, dp+df->size, o + i);
      if ((d->info & CTF_UNION)) break;
    } else if (ctype_isxattrib(df->info, CTA_SUBTYPE)) {
      cconv_substruct_init(cts, ctype_rawchild(cts, df),
			   dp+df->size, o, len, ip);
      if ((d->info & CTF_UNION)) break;
    }  /* Ignore all other entries in the chain. */
  }
}