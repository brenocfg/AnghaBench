#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ endpc; scalar_t__ startpc; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VarInfo ;
struct TYPE_13__ {size_t nuv; size_t* uvmap; int /*<<< orphan*/  vbase; } ;
struct TYPE_12__ {size_t len; } ;
struct TYPE_11__ {int vtop; int /*<<< orphan*/  sb; TYPE_1__* vstack; } ;
typedef  size_t MSize ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ GCstr ;
typedef  TYPE_4__ FuncState ;
typedef  scalar_t__ BCPos ;

/* Variables and functions */
 uintptr_t VARNAME__MAX ; 
 int /*<<< orphan*/  gola_isgotolabel (TYPE_1__*) ; 
 char* lj_buf_more (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lj_buf_putb (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lj_buf_reset (int /*<<< orphan*/ *) ; 
 char* lj_buf_wmem (char*,int /*<<< orphan*/ ,size_t) ; 
 char* lj_strfmt_wuleb128 (char*,scalar_t__) ; 
 size_t sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdata (TYPE_3__*) ; 
 TYPE_3__* strref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t fs_prep_var(LexState *ls, FuncState *fs, size_t *ofsvar)
{
  VarInfo *vs =ls->vstack, *ve;
  MSize i, n;
  BCPos lastpc;
  lj_buf_reset(&ls->sb);  /* Copy to temp. string buffer. */
  /* Store upvalue names. */
  for (i = 0, n = fs->nuv; i < n; i++) {
    GCstr *s = strref(vs[fs->uvmap[i]].name);
    MSize len = s->len+1;
    char *p = lj_buf_more(&ls->sb, len);
    p = lj_buf_wmem(p, strdata(s), len);
    setsbufP(&ls->sb, p);
  }
  *ofsvar = sbuflen(&ls->sb);
  lastpc = 0;
  /* Store local variable names and compressed ranges. */
  for (ve = vs + ls->vtop, vs += fs->vbase; vs < ve; vs++) {
    if (!gola_isgotolabel(vs)) {
      GCstr *s = strref(vs->name);
      BCPos startpc;
      char *p;
      if ((uintptr_t)s < VARNAME__MAX) {
	p = lj_buf_more(&ls->sb, 1 + 2*5);
	*p++ = (char)(uintptr_t)s;
      } else {
	MSize len = s->len+1;
	p = lj_buf_more(&ls->sb, len + 2*5);
	p = lj_buf_wmem(p, strdata(s), len);
      }
      startpc = vs->startpc;
      p = lj_strfmt_wuleb128(p, startpc-lastpc);
      p = lj_strfmt_wuleb128(p, vs->endpc-startpc);
      setsbufP(&ls->sb, p);
      lastpc = startpc;
    }
  }
  lj_buf_putb(&ls->sb, '\0');  /* Terminator for varinfo. */
  return sbuflen(&ls->sb);
}