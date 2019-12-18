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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
usage(int argc, char **argv)
{
	fprintf(stderr,
	    "usage: %s [-hvycdrRk] [-n <nth>] [-f <files>] [-x <xattrs>]\n"
	    "       [-s <bytes>] [-p <path>] [-t <script> ] [-o <phase>]\n",
	    argv[0]);

	fprintf(stderr,
	    "  --help        -h           This help\n"
	    "  --verbose     -v           Increase verbosity\n"
	    "  --verify      -y           Verify xattr contents\n"
	    "  --nth         -n <nth>     Print every nth file\n"
	    "  --files       -f <files>   Set xattrs on N files\n"
	    "  --xattrs      -x <xattrs>  Set N xattrs on each file\n"
	    "  --size        -s <bytes>   Set N bytes per xattr\n"
	    "  --path        -p <path>    Path to files\n"
	    "  --synccaches  -c           Sync caches between phases\n"
	    "  --dropcaches  -d           Drop caches between phases\n"
	    "  --script      -t <script>  Exec script between phases\n"
	    "  --seed        -e <seed>    Random seed value\n"
	    "  --random      -r           Randomly sized xattrs [16-size]\n"
	    "  --randomvalue -R           Random xattr values\n"
	    "  --keep        -k           Don't unlink files\n"
	    "  --only        -o <num>     Only run phase N\n"
	    "                             0=all, 1=create, 2=setxattr,\n"
	    "                             3=getxattr, 4=unlink\n\n");

	return (1);
}