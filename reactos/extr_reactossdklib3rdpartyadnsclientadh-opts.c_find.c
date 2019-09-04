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
struct optioninfo {int dummy; } ;
typedef  int /*<<< orphan*/  comparer_type ;

/* Variables and functions */
 scalar_t__ ads ; 
 struct optioninfo* find1 (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  perquery_options ; 
 int /*<<< orphan*/  usageerr (char*,char const*,char const*) ; 

__attribute__((used)) static const struct optioninfo *find(const char **optp,
				     const char *prefix,
				     comparer_type *comparer) {
  const struct optioninfo *oip;
  const char *opt;

  opt= *optp;
  oip= find1(optp,perquery_options,comparer);
  if (oip) return oip;
  oip= find1(optp,global_options,comparer);
  if (!oip) usageerr("unknown option %s%s",prefix,opt);
  if (ads) usageerr("global option %s%s specified after query domain(s)",prefix,opt);
  return oip;
}