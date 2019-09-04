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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  quitnow (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usageerr(const char *why) {
  fprintf(stderr,
	  "bad usage: %s\n"
	  "usage: adnstest [-<initflagsnum>[,<owninitflags>]] [/<initstring>]\n"
	  "              [ :<typenum>,... ]\n"
	  "              [ [<queryflagsnum>[,<ownqueryflags>]/]<domain> ... ]\n"
	  "initflags:   p  use poll(2) instead of select(2)\n"
	  "             s  use adns_wait with specified query, instead of 0\n"
	  "queryflags:  a  print status abbrevs instead of strings\n"
	  "exit status:  0 ok (though some queries may have failed)\n"
	  "              1 used by test harness to indicate test failed\n"
	  "              2 unable to submit or init or some such\n"
	  "              3 unexpected failure\n"
	  "              4 usage error\n"
	  "              5 operation not supported on this system\n",
	  why);
  quitnow(4);
}