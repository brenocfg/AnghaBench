#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in_addr {scalar_t__ s_addr; } ;
struct server {struct in_addr addr; } ;
typedef  TYPE_1__* adns_state ;
struct TYPE_5__ {int nservers; struct server* servers; } ;

/* Variables and functions */
 int MAXSERVERS ; 
 int /*<<< orphan*/  adns__debug (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__diag (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 

__attribute__((used)) static void addserver(adns_state ads, struct in_addr addr) {
  int i;
  struct server *ss;

  for (i=0; i<ads->nservers; i++) {
    if (ads->servers[i].addr.s_addr == addr.s_addr) {
      adns__debug(ads,-1,0,"duplicate nameserver %s ignored",inet_ntoa(addr));
      return;
    }
  }

  if (ads->nservers>=MAXSERVERS) {
    adns__diag(ads,-1,0,"too many nameservers, ignoring %s",inet_ntoa(addr));
    return;
  }

  ss= ads->servers+ads->nservers;
  ss->addr= addr;
  ads->nservers++;
}