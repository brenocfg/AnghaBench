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
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_status ;
typedef  TYPE_1__* adns_query ;
struct TYPE_4__ {int /*<<< orphan*/  cname_begin; int /*<<< orphan*/  cname_dglen; int /*<<< orphan*/  cname_dgram; int /*<<< orphan*/  query_dglen; int /*<<< orphan*/  query_dgram; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_HDRSIZE ; 
 int /*<<< orphan*/  adns__findrr_anychk (TYPE_1__*,int,int /*<<< orphan*/  const*,int,int*,int*,int*,unsigned long*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

adns_status adns__findrr(adns_query qu, int serv,
			 const byte *dgram, int dglen, int *cbyte_io,
			 int *type_r, int *class_r, unsigned long *ttl_r,
			 int *rdlen_r, int *rdstart_r,
			 int *ownermatchedquery_r) {
  if (!ownermatchedquery_r) {
    return adns__findrr_anychk(qu,serv,
			       dgram,dglen,cbyte_io,
			       type_r,class_r,ttl_r,rdlen_r,rdstart_r,
			       0,0,0, 0);
  } else if (!qu->cname_dgram) {
    return adns__findrr_anychk(qu,serv,
			       dgram,dglen,cbyte_io,
			       type_r,class_r,ttl_r,rdlen_r,rdstart_r,
			       qu->query_dgram,qu->query_dglen,DNS_HDRSIZE,
			       ownermatchedquery_r);
  } else {
    return adns__findrr_anychk(qu,serv,
			       dgram,dglen,cbyte_io,
			       type_r,class_r,ttl_r,rdlen_r,rdstart_r,
			       qu->cname_dgram,qu->cname_dglen,qu->cname_begin,
			       ownermatchedquery_r);
  }
}