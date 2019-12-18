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
 scalar_t__ ExprMatch (char*,char*) ; 

int matchname (int arg,int argc,char **argv,char *fname)
{
  if (arg == argc)      /* no arguments given (untgz tgzarchive) */
    return 1;

  while (arg < argc)
    if (ExprMatch(fname,argv[arg++]))
      return 1;

  return 0; /* ignore this for the moment being */
}