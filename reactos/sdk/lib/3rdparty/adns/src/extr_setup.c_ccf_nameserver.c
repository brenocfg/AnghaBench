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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  addserver (int /*<<< orphan*/ ,struct in_addr) ; 
 int /*<<< orphan*/  adns__debug (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configparseerr (int /*<<< orphan*/ ,char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  inet_aton (char const*,struct in_addr*) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 

__attribute__((used)) static void ccf_nameserver(adns_state ads, const char *fn, int lno, const char *buf) {
  struct in_addr ia;

  if (!inet_aton(buf,&ia)) {
    configparseerr(ads,fn,lno,"invalid nameserver address `%s'",buf);
    return;
  }
  adns__debug(ads,-1,0,"using nameserver %s",inet_ntoa(ia));
  addserver(ads,ia);
}