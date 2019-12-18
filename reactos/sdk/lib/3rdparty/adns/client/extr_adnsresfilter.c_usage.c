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
 scalar_t__ EOF ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outputerr () ; 
 scalar_t__ printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysfail (char*) ; 

__attribute__((used)) static void usage(void) {
  if (printf("usage: adnsresfilter [<options ...>]\n"
	     "       adnsresfilter  -h|--help | --version\n"
	     "options: -t<milliseconds>|--timeout <milliseconds>\n"
	     "         -w|--wait        (always wait for queries to time out or fail)\n"
	     "         -b|--brackets    (require [...] around IP addresses)\n"
	     "         -a|--address     (always include [address] in output)\n"
	     "         -u|--unchecked   (do not forward map for checking)\n"
	     "         --config <text>  (use this instead of resolv.conf)\n"
	     "         --debug          (turn on adns resolver debugging)\n"
	     "Timeout is the maximum amount to delay any particular bit of output for.\n"
	     "Lookups will go on in the background.  Default timeout = 1000 (ms).\n")
      == EOF) outputerr();
  if (fflush(stdout)) sysfail("flush stdout");
}