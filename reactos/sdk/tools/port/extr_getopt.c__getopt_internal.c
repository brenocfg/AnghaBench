#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct option {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  optopt; int /*<<< orphan*/  optarg; int /*<<< orphan*/  optind; int /*<<< orphan*/  opterr; } ;

/* Variables and functions */
 int _getopt_internal_r (int,char**,char const*,struct option const*,int*,int,TYPE_1__*,int) ; 
 TYPE_1__ getopt_data ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  opterr ; 
 int /*<<< orphan*/  optind ; 
 int /*<<< orphan*/  optopt ; 

int
_getopt_internal (int argc, char **argv, const char *optstring,
		  const struct option *longopts, int *longind, int long_only,
		  int posixly_correct)
{
  int result;

  getopt_data.optind = optind;
  getopt_data.opterr = opterr;

  result = _getopt_internal_r (argc, argv, optstring, longopts,
			       longind, long_only, &getopt_data,
			       posixly_correct);

  optind = getopt_data.optind;
  optarg = getopt_data.optarg;
  optopt = getopt_data.optopt;

  return result;
}