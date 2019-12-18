#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_1__ GCstr ;

/* Variables and functions */
 int /*<<< orphan*/  STRFMT_G14 ; 
 scalar_t__ STRFMT_MAXBUF_INT ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 char* lj_buf_more (int /*<<< orphan*/ *,scalar_t__) ; 
 char* lj_buf_wmem (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * lj_strfmt_putfnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lj_strfmt_wint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_getint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strVdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdata (TYPE_1__*) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

SBuf *lj_buf_puttab(SBuf *sb, GCtab *t, GCstr *sep, int32_t i, int32_t e)
{
  MSize seplen = sep ? sep->len : 0;
  if (i <= e) {
    for (;;) {
      cTValue *o = lj_tab_getint(t, i);
      char *p;
      if (!o) {
      badtype:  /* Error: bad element type. */
	setsbufP(sb, (void *)(intptr_t)i);  /* Store failing index. */
	return NULL;
      } else if (tvisstr(o)) {
	MSize len = strV(o)->len;
	p = lj_buf_wmem(lj_buf_more(sb, len + seplen), strVdata(o), len);
      } else if (tvisint(o)) {
	p = lj_strfmt_wint(lj_buf_more(sb, STRFMT_MAXBUF_INT+seplen), intV(o));
      } else if (tvisnum(o)) {
	p = lj_buf_more(lj_strfmt_putfnum(sb, STRFMT_G14, numV(o)), seplen);
      } else {
	goto badtype;
      }
      if (i++ == e) {
	setsbufP(sb, p);
	break;
      }
      if (seplen) p = lj_buf_wmem(p, strdata(sep), seplen);
      setsbufP(sb, p);
    }
  }
  return sb;
}