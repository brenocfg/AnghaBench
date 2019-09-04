#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ used; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  findlabel_state ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_status ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_queryflags ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int /*<<< orphan*/  adns__findlabel_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int,int*) ; 
 int /*<<< orphan*/  adns__parse_domain_more (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

adns_status adns__parse_domain(adns_state ads, int serv, adns_query qu,
			       vbuf *vb, adns_queryflags flags,
			       const byte *dgram, int dglen, int *cbyte_io, int max) {
  findlabel_state fls;

  adns__findlabel_start(&fls,ads, serv,qu, dgram,dglen,max, *cbyte_io,cbyte_io);
  vb->used= 0;
  return adns__parse_domain_more(&fls,ads,qu, vb,flags,dgram);
}