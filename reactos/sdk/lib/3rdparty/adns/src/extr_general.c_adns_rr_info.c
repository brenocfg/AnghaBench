#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int used; scalar_t__ buf; } ;
typedef  TYPE_1__ vbuf ;
struct TYPE_9__ {char* rrtname; char* fmtname; int rrsz; scalar_t__ (* convstring ) (TYPE_1__*,void const*) ;} ;
typedef  TYPE_2__ typeinfo ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
typedef  int /*<<< orphan*/  adns_rrtype ;

/* Variables and functions */
 TYPE_2__* adns__findtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__vbuf_append (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  adns__vbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  adns__vbuf_init (TYPE_1__*) ; 
 scalar_t__ adns_s_nomemory ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ adns_s_unknownrrtype ; 
 int /*<<< orphan*/  assert (int) ; 
 char* realloc (scalar_t__,size_t) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ stub1 (TYPE_1__*,void const*) ; 

adns_status adns_rr_info(adns_rrtype type,
			 const char **rrtname_r, const char **fmtname_r,
			 int *len_r,
			 const void *datap, char **data_r) {
  const typeinfo *typei;
  vbuf vb;
  adns_status st;

  typei= adns__findtype(type);
  if (!typei) return adns_s_unknownrrtype;

  if (rrtname_r) *rrtname_r= typei->rrtname;
  if (fmtname_r) *fmtname_r= typei->fmtname;
  if (len_r) *len_r= typei->rrsz;

  if (!datap) return adns_s_ok;

  adns__vbuf_init(&vb);
  st= typei->convstring(&vb,datap);
  if (st) goto x_freevb;
  if (!adns__vbuf_append(&vb,(byte*)"",1)) { st= adns_s_nomemory; goto x_freevb; }
  assert((int)strlen((char*)vb.buf) == vb.used-1);
  *data_r= realloc(vb.buf, (size_t) vb.used);
  if (!*data_r) *data_r= (char*)vb.buf;
  return adns_s_ok;

 x_freevb:
  adns__vbuf_free(&vb);
  return st;
}