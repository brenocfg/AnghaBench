#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* qu; int /*<<< orphan*/  dglen; int /*<<< orphan*/  dgram; int /*<<< orphan*/  serv; } ;
typedef  TYPE_1__ parseinfo ;
typedef  int /*<<< orphan*/  parsedomain_flags ;
typedef  scalar_t__ adns_status ;
struct TYPE_8__ {size_t used; int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {TYPE_4__ vb; int /*<<< orphan*/  ads; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_NOMEM ; 
 char* adns__alloc_interim (TYPE_3__*,size_t) ; 
 scalar_t__ adns__parse_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static adns_status pap_domain(const parseinfo *pai, int *cbyte_io, int max,
			      char **domain_r, parsedomain_flags flags) {
  adns_status st;
  char *dm;

  st= adns__parse_domain(pai->qu->ads, pai->serv, pai->qu, &pai->qu->vb, flags,
			 pai->dgram,pai->dglen, cbyte_io, max);
  if (st) return st;
  if (!pai->qu->vb.used) return adns_s_invaliddata;

  dm= adns__alloc_interim(pai->qu, (size_t) pai->qu->vb.used+1);
  if (!dm) R_NOMEM;

  dm[pai->qu->vb.used]= 0;
  memcpy(dm,pai->qu->vb.buf, (size_t) pai->qu->vb.used);

  *domain_r= dm;
  return adns_s_ok;
}