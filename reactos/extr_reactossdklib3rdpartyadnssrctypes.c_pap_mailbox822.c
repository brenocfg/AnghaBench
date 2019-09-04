#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t used; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ vbuf ;
struct TYPE_13__ {unsigned char* dgram; TYPE_8__* qu; int /*<<< orphan*/  ads; int /*<<< orphan*/  dglen; } ;
typedef  TYPE_2__ parseinfo ;
typedef  int /*<<< orphan*/  findlabel_state ;
typedef  unsigned char const byte ;
typedef  scalar_t__ adns_status ;
struct TYPE_14__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_NOMEM ; 
 char* adns__alloc_interim (TYPE_8__*,size_t) ; 
 scalar_t__ adns__findlabel_next (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  adns__findlabel_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_8__*,unsigned char*,int /*<<< orphan*/ ,int,int,int*) ; 
 scalar_t__ adns__parse_domain_more (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,TYPE_1__*,int /*<<< orphan*/ ,unsigned char*) ; 
 int adns__vbuf_append (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  adns__vbuf_appendq (TYPE_1__*,unsigned char const*,int) ; 
 int adns__vbuf_appendstr (TYPE_1__*,char*) ; 
 int adns__vbuf_ensure (TYPE_1__*,int) ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ ctype_822special (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static adns_status pap_mailbox822(const parseinfo *pai, int *cbyte_io, int max,
				  char **mb_r) {
  int lablen, labstart, i, needquote, c, r, neednorm;
  const unsigned char *p;
  char *str;
  findlabel_state fls;
  adns_status st;
  vbuf *vb;

  vb= &pai->qu->vb;
  vb->used= 0;
  adns__findlabel_start(&fls, pai->ads,
			-1, pai->qu,
			pai->dgram, pai->dglen, max,
			*cbyte_io, cbyte_io);
  st= adns__findlabel_next(&fls,&lablen,&labstart);
  if (!lablen) {
    adns__vbuf_appendstr(vb,".");
    goto x_ok;
  }

  neednorm= 1;
  for (i=0, needquote=0, p= pai->dgram+labstart; i<lablen; i++) {
    c= *p++;
    if ((c&~128) < 32 || (c&~128) == 127) return adns_s_invaliddata;
    if (c == '.' && !neednorm) neednorm= 1;
    else if (c==' ' || c>=127 || ctype_822special(c)) needquote++;
    else neednorm= 0;
  }

  if (needquote || neednorm) {
    r= adns__vbuf_ensure(vb, lablen+needquote+4); if (!r) R_NOMEM;
    adns__vbuf_appendq(vb,(byte*)"\"",1);
    for (i=0, needquote=0, p= pai->dgram+labstart; i<lablen; i++, p++) {
      c= *p;
      if (c == '"' || c=='\\') adns__vbuf_appendq(vb,(byte*)"\\",1);
      adns__vbuf_appendq(vb,p,1);
    }
    adns__vbuf_appendq(vb,(byte*)"\"",1);
  } else {
    r= adns__vbuf_append(vb, pai->dgram+labstart, lablen); if (!r) R_NOMEM;
  }

  r= adns__vbuf_appendstr(vb,"@"); if (!r) R_NOMEM;

  st= adns__parse_domain_more(&fls,pai->ads, pai->qu,vb,0, pai->dgram);
  if (st) return st;

 x_ok:
  str= adns__alloc_interim(pai->qu, (size_t) vb->used+1); if (!str) R_NOMEM;
  memcpy(str,vb->buf,(size_t) vb->used);
  str[vb->used]= 0;
  *mb_r= str;
  return adns_s_ok;
}