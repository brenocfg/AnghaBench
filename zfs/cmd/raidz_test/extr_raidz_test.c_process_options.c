#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long long rto_ashift; unsigned long long rto_offset; unsigned long long rto_dcols; unsigned long long rto_dsize; size_t rto_sweep_timeout; int rto_sweep; int rto_benchmark; int rto_gdb; int rto_sanity; int /*<<< orphan*/  rto_v; } ;
typedef  TYPE_1__ raidz_test_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t MAX (int,size_t) ; 
 unsigned long long MIN (int,size_t) ; 
 int SPA_MAXBLOCKSHIFT ; 
 int SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 TYPE_1__ rto_opts ; 
 int /*<<< orphan*/  rto_opts_defaults ; 
 size_t strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_options(int argc, char **argv)
{
	size_t value;
	int opt;

	raidz_test_opts_t *o = &rto_opts;

	bcopy(&rto_opts_defaults, o, sizeof (*o));

	while ((opt = getopt(argc, argv, "TDBSvha:o:d:s:t:")) != -1) {
		value = 0;

		switch (opt) {
		case 'a':
			value = strtoull(optarg, NULL, 0);
			o->rto_ashift = MIN(13, MAX(9, value));
			break;
		case 'o':
			value = strtoull(optarg, NULL, 0);
			o->rto_offset = ((1ULL << MIN(12, value)) >> 9) << 9;
			break;
		case 'd':
			value = strtoull(optarg, NULL, 0);
			o->rto_dcols = MIN(255, MAX(1, value));
			break;
		case 's':
			value = strtoull(optarg, NULL, 0);
			o->rto_dsize = 1ULL <<  MIN(SPA_MAXBLOCKSHIFT,
			    MAX(SPA_MINBLOCKSHIFT, value));
			break;
		case 't':
			value = strtoull(optarg, NULL, 0);
			o->rto_sweep_timeout = value;
			break;
		case 'v':
			o->rto_v++;
			break;
		case 'S':
			o->rto_sweep = 1;
			break;
		case 'B':
			o->rto_benchmark = 1;
			break;
		case 'D':
			o->rto_gdb = 1;
			break;
		case 'T':
			o->rto_sanity = 1;
			break;
		case 'h':
			usage(B_TRUE);
			break;
		case '?':
		default:
			usage(B_FALSE);
			break;
		}
	}
}