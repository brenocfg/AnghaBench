#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
typedef  int /*<<< orphan*/  findlabel_state ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_rrtype ;
typedef  int /*<<< orphan*/  adns_queryflags ;

/* Variables and functions */
 int /*<<< orphan*/  MKQUERY_ADDB (int) ; 
 int /*<<< orphan*/  MKQUERY_START (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MKQUERY_STOP (int /*<<< orphan*/ *) ; 
 scalar_t__ adns__findlabel_next (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  adns__findlabel_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ adns_s_ok ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ mkquery_footer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mkquery_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 

adns_status adns__mkquery_frdgram(adns_state ads, vbuf *vb, int *id_r,
				  const byte *qd_dgram, int qd_dglen, int qd_begin,
				  adns_rrtype type, adns_queryflags flags) {
  byte *rqp;
  findlabel_state fls;
  int lablen, labstart;
  adns_status st;

  st= mkquery_header(ads,vb,id_r,qd_dglen); if (st) return st;

  MKQUERY_START(vb);

  adns__findlabel_start(&fls,ads,-1,0,qd_dgram,qd_dglen,qd_dglen,qd_begin,0);
  for (;;) {
    st= adns__findlabel_next(&fls,&lablen,&labstart); assert(!st);
    if (!lablen) break;
    assert(lablen<255);
    MKQUERY_ADDB(lablen);
    memcpy(rqp,qd_dgram+labstart, (size_t) lablen);
    rqp+= lablen;
  }
  MKQUERY_ADDB(0);

  MKQUERY_STOP(vb);

  st= mkquery_footer(vb,type);

  return adns_s_ok;
}