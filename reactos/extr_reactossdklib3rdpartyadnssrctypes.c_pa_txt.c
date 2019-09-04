#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  qu; int /*<<< orphan*/ * dgram; } ;
typedef  TYPE_1__ parseinfo ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
struct TYPE_7__ {int i; scalar_t__ str; } ;
typedef  TYPE_2__ adns_rr_intstr ;

/* Variables and functions */
 int /*<<< orphan*/  GET_B (int,int) ; 
 int /*<<< orphan*/  R_NOMEM ; 
 TYPE_2__* adns__alloc_interim (int /*<<< orphan*/ ,int) ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pap_qstring (TYPE_1__ const*,int*,int,int*,scalar_t__*) ; 

__attribute__((used)) static adns_status pa_txt(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_intstr **rrp= datap, *table, *te;
  const byte *dgram= pai->dgram;
  int ti, tc, l, startbyte;
  adns_status st;

  startbyte= cbyte;
  if (cbyte >= max) return adns_s_invaliddata;
  tc= 0;
  while (cbyte < max) {
    GET_B(cbyte,l);
    cbyte+= l;
    tc++;
  }
  if (cbyte != max || !tc) return adns_s_invaliddata;

  table= adns__alloc_interim(pai->qu,sizeof(*table)*(tc+1));
  if (!table) R_NOMEM;

  for (cbyte=startbyte, ti=0, te=table; ti<tc; ti++, te++) {
    st= pap_qstring(pai, &cbyte, max, &te->i, &te->str);
    if (st) return st;
  }
  assert(cbyte == max);

  te->i= -1;
  te->str= 0;

  *rrp= table;
  return adns_s_ok;
}