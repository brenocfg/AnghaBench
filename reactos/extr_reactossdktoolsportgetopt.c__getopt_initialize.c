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
struct _getopt_data {int optind; int __first_nonopt; int __last_nonopt; int __initialized; void* __ordering; int /*<<< orphan*/ * __nextchar; } ;

/* Variables and functions */
 void* PERMUTE ; 
 void* REQUIRE_ORDER ; 
 void* RETURN_IN_ORDER ; 
 int /*<<< orphan*/  getenv (char*) ; 

__attribute__((used)) static const char *
_getopt_initialize (int argc,
		    char **argv, const char *optstring,
		    struct _getopt_data *d, int posixly_correct)
{
  /* Start processing options with ARGV-element 1 (since ARGV-element 0
     is the program name); the sequence of previously skipped
     non-option ARGV-elements is empty.  */
  if (d->optind == 0)
    d->optind = 1;

  d->__first_nonopt = d->__last_nonopt = d->optind;
  d->__nextchar = NULL;

  /* Determine how to handle the ordering of options and nonoptions.  */
  if (optstring[0] == '-')
    {
      d->__ordering = RETURN_IN_ORDER;
      ++optstring;
    }
  else if (optstring[0] == '+')
    {
      d->__ordering = REQUIRE_ORDER;
      ++optstring;
    }
  else if (posixly_correct || !!getenv ("POSIXLY_CORRECT"))
    d->__ordering = REQUIRE_ORDER;
  else
    d->__ordering = PERMUTE;

  d->__initialized = 1;
  return optstring;
}