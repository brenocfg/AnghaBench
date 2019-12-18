#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* rto_ashift; int /*<<< orphan*/  rto_v; int /*<<< orphan*/  rto_dsize; int /*<<< orphan*/  rto_dcols; int /*<<< orphan*/  rto_offset; } ;
typedef  TYPE_1__ raidz_test_opts_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {scalar_t__ rto_sweep; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 TYPE_3__ rto_opts ; 
 TYPE_1__ rto_opts_defaults ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void usage(boolean_t requested)
{
	const raidz_test_opts_t *o = &rto_opts_defaults;

	FILE *fp = requested ? stdout : stderr;

	(void) fprintf(fp, "Usage:\n"
	    "\t[-a zio ashift (default: %zu)]\n"
	    "\t[-o zio offset, exponent radix 2 (default: %zu)]\n"
	    "\t[-d number of raidz data columns (default: %zu)]\n"
	    "\t[-s zio size, exponent radix 2 (default: %zu)]\n"
	    "\t[-S parameter sweep (default: %s)]\n"
	    "\t[-t timeout for parameter sweep test]\n"
	    "\t[-B benchmark all raidz implementations]\n"
	    "\t[-v increase verbosity (default: %zu)]\n"
	    "\t[-h (print help)]\n"
	    "\t[-T test the test, see if failure would be detected]\n"
	    "\t[-D debug (attach gdb on SIGSEGV)]\n"
	    "",
	    o->rto_ashift,				/* -a */
	    ilog2(o->rto_offset),			/* -o */
	    o->rto_dcols,				/* -d */
	    ilog2(o->rto_dsize),			/* -s */
	    rto_opts.rto_sweep ? "yes" : "no",		/* -S */
	    o->rto_v);					/* -d */

	exit(requested ? 0 : 1);
}