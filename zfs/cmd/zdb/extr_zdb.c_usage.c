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
 char* cmdname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void) fprintf(stderr,
	    "Usage:\t%s [-AbcdDFGhikLMPsvX] [-e [-V] [-p <path> ...]] "
	    "[-I <inflight I/Os>]\n"
	    "\t\t[-o <var>=<value>]... [-t <txg>] [-U <cache>] [-x <dumpdir>]\n"
	    "\t\t[<poolname> [<object> ...]]\n"
	    "\t%s [-AdiPv] [-e [-V] [-p <path> ...]] [-U <cache>] <dataset>\n"
	    "\t\t[<object> ...]\n"
	    "\t%s [-v] <bookmark>\n"
	    "\t%s -C [-A] [-U <cache>]\n"
	    "\t%s -l [-Aqu] <device>\n"
	    "\t%s -m [-AFLPX] [-e [-V] [-p <path> ...]] [-t <txg>] "
	    "[-U <cache>]\n\t\t<poolname> [<vdev> [<metaslab> ...]]\n"
	    "\t%s -O <dataset> <path>\n"
	    "\t%s -R [-A] [-e [-V] [-p <path> ...]] [-U <cache>]\n"
	    "\t\t<poolname> <vdev>:<offset>:<size>[:<flags>]\n"
	    "\t%s -E [-A] word0:word1:...:word15\n"
	    "\t%s -S [-AP] [-e [-V] [-p <path> ...]] [-U <cache>] "
	    "<poolname>\n\n",
	    cmdname, cmdname, cmdname, cmdname, cmdname, cmdname, cmdname,
	    cmdname, cmdname, cmdname);

	(void) fprintf(stderr, "    Dataset name must include at least one "
	    "separator character '/' or '@'\n");
	(void) fprintf(stderr, "    If dataset name is specified, only that "
	    "dataset is dumped\n");
	(void) fprintf(stderr, "    If object numbers are specified, only "
	    "those objects are dumped\n\n");
	(void) fprintf(stderr, "    Options to control amount of output:\n");
	(void) fprintf(stderr, "        -b block statistics\n");
	(void) fprintf(stderr, "        -c checksum all metadata (twice for "
	    "all data) blocks\n");
	(void) fprintf(stderr, "        -C config (or cachefile if alone)\n");
	(void) fprintf(stderr, "        -d dataset(s)\n");
	(void) fprintf(stderr, "        -D dedup statistics\n");
	(void) fprintf(stderr, "        -E decode and display block from an "
	    "embedded block pointer\n");
	(void) fprintf(stderr, "        -h pool history\n");
	(void) fprintf(stderr, "        -i intent logs\n");
	(void) fprintf(stderr, "        -l read label contents\n");
	(void) fprintf(stderr, "        -k examine the checkpointed state "
	    "of the pool\n");
	(void) fprintf(stderr, "        -L disable leak tracking (do not "
	    "load spacemaps)\n");
	(void) fprintf(stderr, "        -m metaslabs\n");
	(void) fprintf(stderr, "        -M metaslab groups\n");
	(void) fprintf(stderr, "        -O perform object lookups by path\n");
	(void) fprintf(stderr, "        -R read and display block from a "
	    "device\n");
	(void) fprintf(stderr, "        -s report stats on zdb's I/O\n");
	(void) fprintf(stderr, "        -S simulate dedup to measure effect\n");
	(void) fprintf(stderr, "        -v verbose (applies to all "
	    "others)\n\n");
	(void) fprintf(stderr, "    Below options are intended for use "
	    "with other options:\n");
	(void) fprintf(stderr, "        -A ignore assertions (-A), enable "
	    "panic recovery (-AA) or both (-AAA)\n");
	(void) fprintf(stderr, "        -e pool is exported/destroyed/"
	    "has altroot/not in a cachefile\n");
	(void) fprintf(stderr, "        -F attempt automatic rewind within "
	    "safe range of transaction groups\n");
	(void) fprintf(stderr, "        -G dump zfs_dbgmsg buffer before "
	    "exiting\n");
	(void) fprintf(stderr, "        -I <number of inflight I/Os> -- "
	    "specify the maximum number of\n           "
	    "checksumming I/Os [default is 200]\n");
	(void) fprintf(stderr, "        -o <variable>=<value> set global "
	    "variable to an unsigned 32-bit integer\n");
	(void) fprintf(stderr, "        -p <path> -- use one or more with "
	    "-e to specify path to vdev dir\n");
	(void) fprintf(stderr, "        -P print numbers in parseable form\n");
	(void) fprintf(stderr, "        -q don't print label contents\n");
	(void) fprintf(stderr, "        -t <txg> -- highest txg to use when "
	    "searching for uberblocks\n");
	(void) fprintf(stderr, "        -u uberblock\n");
	(void) fprintf(stderr, "        -U <cachefile_path> -- use alternate "
	    "cachefile\n");
	(void) fprintf(stderr, "        -V do verbatim import\n");
	(void) fprintf(stderr, "        -x <dumpdir> -- "
	    "dump all read blocks into specified directory\n");
	(void) fprintf(stderr, "        -X attempt extreme rewind (does not "
	    "work with dataset)\n");
	(void) fprintf(stderr, "        -Y attempt all reconstruction "
	    "combinations for split blocks\n");
	(void) fprintf(stderr, "Specify an option more than once (e.g. -bb) "
	    "to make only that option verbose\n");
	(void) fprintf(stderr, "Default is to dump everything non-verbosely\n");
	exit(1);
}