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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  scalar_t__ adns_rrtype ;
typedef  int /*<<< orphan*/  adns_queryflags ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ adns_r_ptr ; 
 scalar_t__ adns_r_ptr_raw ; 
 int adns_submit_reverse_any (int /*<<< orphan*/ ,struct sockaddr const*,char*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int adns_submit_reverse(adns_state ads,
			const struct sockaddr *addr,
			adns_rrtype type,
			adns_queryflags flags,
			void *context,
			adns_query *query_r) {
  if (type != adns_r_ptr && type != adns_r_ptr_raw) return EINVAL;
  return adns_submit_reverse_any(ads,addr,"in-addr.arpa",type,flags,context,query_r);
}