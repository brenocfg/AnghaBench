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
struct option {int dummy; } ;
struct _getopt_data {int dummy; } ;

/* Variables and functions */
 int _getopt_internal_r (int,char**,char const*,struct option const*,int*,int /*<<< orphan*/ ,struct _getopt_data*,int /*<<< orphan*/ ) ; 

int
_getopt_long_r (int argc, char **argv, const char *options,
		const struct option *long_options, int *opt_index,
		struct _getopt_data *d)
{
  return _getopt_internal_r (argc, argv, options, long_options, opt_index,
			     0, d, 0);
}