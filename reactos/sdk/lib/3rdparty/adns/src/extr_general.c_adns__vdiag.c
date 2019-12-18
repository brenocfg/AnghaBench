#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
typedef  int /*<<< orphan*/  va_list ;
typedef  TYPE_3__* adns_state ;
typedef  TYPE_4__* adns_query ;
typedef  int adns_initflags ;
struct TYPE_10__ {TYPE_1__* typei; int /*<<< orphan*/  query_dglen; int /*<<< orphan*/  query_dgram; int /*<<< orphan*/  ads; } ;
struct TYPE_9__ {int iflags; int /*<<< orphan*/  diagfile; TYPE_2__* servers; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {char* rrtname; char* fmtname; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_HDRSIZE ; 
 char* adns__diag_domain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__vbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns__vbuf_init (int /*<<< orphan*/ *) ; 
 int adns_if_debug ; 
 int adns_if_logpid ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void adns__vdiag(adns_state ads, const char *pfx, adns_initflags prevent,
		 int serv, adns_query qu, const char *fmt, va_list al) {
  const char *bef, *aft;
  vbuf vb;

  if (!ads->diagfile ||
      (!(ads->iflags & adns_if_debug) && (!prevent || (ads->iflags & prevent))))
    return;

  if (ads->iflags & adns_if_logpid) {
    fprintf(ads->diagfile,"adns%s [%ld]: ",pfx,(long)getpid());
  } else {
    fprintf(ads->diagfile,"adns%s: ",pfx);
  }

  vfprintf(ads->diagfile,fmt,al);

  bef= " (";
  aft= "\n";

  if (qu && qu->query_dgram) {
    adns__vbuf_init(&vb);
    fprintf(ads->diagfile,"%sQNAME=%s, QTYPE=%s",
	    bef,
	    adns__diag_domain(qu->ads,-1,0, &vb,
			      qu->query_dgram,qu->query_dglen,DNS_HDRSIZE),
	    qu->typei ? qu->typei->rrtname : "<unknown>");
    if (qu->typei && qu->typei->fmtname)
      fprintf(ads->diagfile,"(%s)",qu->typei->fmtname);
    bef=", "; aft=")\n";
    adns__vbuf_free(&vb);
  }

  if (serv>=0) {
    fprintf(ads->diagfile,"%sNS=%s",bef,inet_ntoa(ads->servers[serv].addr));
    bef=", "; aft=")\n";
  }

  fputs(aft,ads->diagfile);
}