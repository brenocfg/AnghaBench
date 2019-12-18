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
struct TYPE_8__ {scalar_t__ used; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_status ;
typedef  TYPE_2__* adns_state ;
struct TYPE_9__ {int /*<<< orphan*/  nextid; } ;

/* Variables and functions */
 scalar_t__ DNS_HDRSIZE ; 
 int /*<<< orphan*/  MKQUERY_ADDB (int) ; 
 int /*<<< orphan*/  MKQUERY_ADDW (int) ; 
 int /*<<< orphan*/  MKQUERY_START (TYPE_1__*) ; 
 int /*<<< orphan*/  MKQUERY_STOP (TYPE_1__*) ; 
 int /*<<< orphan*/  adns__vbuf_ensure (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  adns_s_nomemory ; 
 int /*<<< orphan*/  adns_s_ok ; 

__attribute__((used)) static adns_status mkquery_header(adns_state ads, vbuf *vb, int *id_r, int qdlen) {
  int id;
  byte *rqp;

  if (!adns__vbuf_ensure(vb,DNS_HDRSIZE+qdlen+4)) return adns_s_nomemory;

  vb->used= 0;
  MKQUERY_START(vb);

  *id_r= id= (ads->nextid++) & 0x0ffff;
  MKQUERY_ADDW(id);
  MKQUERY_ADDB(0x01); /* QR=Q(0), OPCODE=QUERY(0000), !AA, !TC, RD */
  MKQUERY_ADDB(0x00); /* !RA, Z=000, RCODE=NOERROR(0000) */
  MKQUERY_ADDW(1); /* QDCOUNT=1 */
  MKQUERY_ADDW(0); /* ANCOUNT=0 */
  MKQUERY_ADDW(0); /* NSCOUNT=0 */
  MKQUERY_ADDW(0); /* ARCOUNT=0 */

  MKQUERY_STOP(vb);

  return adns_s_ok;
}