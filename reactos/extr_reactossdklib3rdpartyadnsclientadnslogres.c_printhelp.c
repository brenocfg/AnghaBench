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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void printhelp(FILE *file) {
  fputs("usage: adnslogres [<options>] [<logfile>]\n"
	"       adnslogres --version|--help\n"
	"options: -c <concurrency>  set max number of outstanding queries\n"
#ifdef HAVE_POLL
	"         -p                use poll(2) instead of select(2)\n"
#endif
	"         -d                turn on debugging\n"
	"         -C <config>       use instead of contents of resolv.conf\n",
	stdout);
}