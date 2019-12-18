#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buf; scalar_t__ used; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 scalar_t__ adns__parse_domain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int*,int) ; 
 scalar_t__ adns__vbuf_append (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ adns__vbuf_appendstr (TYPE_1__*,char*) ; 
 scalar_t__ adns_s_nomemory ; 
 char* adns_strerror (scalar_t__) ; 
 int /*<<< orphan*/  pdf_quoteok ; 

const char *adns__diag_domain(adns_state ads, int serv, adns_query qu,
			      vbuf *vb, const byte *dgram, int dglen, int cbyte) {
  adns_status st;

  st= adns__parse_domain(ads,serv,qu,vb, pdf_quoteok, dgram,dglen,&cbyte,dglen);
  if (st == adns_s_nomemory) {
    return "<cannot report domain... out of memory>";
  }
  if (st) {
    vb->used= 0;
    if (!(adns__vbuf_appendstr(vb,"<bad format... ") &&
	  adns__vbuf_appendstr(vb,adns_strerror(st)) &&
	  adns__vbuf_appendstr(vb,">") &&
	  adns__vbuf_append(vb,(byte*)"",1))) {
      return "<cannot report bad format... out of memory>";
    }
  }
  if (!vb->used) {
    adns__vbuf_appendstr(vb,"<truncated ...>");
    adns__vbuf_append(vb,(byte*)"",1);
  }
  return (char*)vb->buf;
}