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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct query_node {int /*<<< orphan*/  qu; int /*<<< orphan*/  owner; } ;
struct optioninfo {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  LIST_LINK_TAIL (int /*<<< orphan*/ ,struct query_node*) ; 
 scalar_t__ adns_r_none ; 
 scalar_t__ adns_r_ptr ; 
 int adns_submit_reverse (int /*<<< orphan*/ ,struct sockaddr*,scalar_t__,int,struct query_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ads ; 
 int /*<<< orphan*/  inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outstanding ; 
 scalar_t__ ov_type ; 
 int /*<<< orphan*/  prep_query (struct query_node**,int*) ; 
 int /*<<< orphan*/  sysfail (char*,int) ; 
 int /*<<< orphan*/  usageerr (char*,char const*) ; 
 int /*<<< orphan*/  xstrsave (char const*) ; 

void of_ptr(const struct optioninfo *oi, const char *arg, const char *arg2) {
  struct query_node *qun;
  int quflags, r;
  struct sockaddr_in sa;

  memset(&sa,0,sizeof(sa));
  sa.sin_family= AF_INET;
  if (!inet_aton(arg,&sa.sin_addr)) usageerr("invalid IP address %s",arg);

  prep_query(&qun,&quflags);
  qun->owner= xstrsave(arg);
  r= adns_submit_reverse(ads,
			 (struct sockaddr*)&sa,
			 ov_type == adns_r_none ? adns_r_ptr : ov_type,
			 quflags,
			 qun,
			 &qun->qu);
  if (r) sysfail("adns_submit_reverse",r);

  LIST_LINK_TAIL(outstanding,qun);
}