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
struct _getopt_data {int opterr; char* optarg; int optind; char* __nextchar; int __last_nonopt; int __first_nonopt; scalar_t__ __ordering; char optopt; int /*<<< orphan*/  __initialized; } ;

/* Variables and functions */
 scalar_t__ NONOPTION_P ; 
 scalar_t__ PERMUTE ; 
 scalar_t__ REQUIRE_ORDER ; 
 char* _ (char*) ; 
 char* _getopt_initialize (int,char**,char const*,struct _getopt_data*,int) ; 
 int /*<<< orphan*/  exchange (char**,struct _getopt_data*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char) ; 
 int process_long_option (int,char**,char const*,struct option const*,int*,int,struct _getopt_data*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
_getopt_internal_r (int argc, char **argv, const char *optstring,
		    const struct option *longopts, int *longind,
		    int long_only, struct _getopt_data *d, int posixly_correct)
{
  int print_errors = d->opterr;

  if (argc < 1)
    return -1;

  d->optarg = NULL;

  if (d->optind == 0 || !d->__initialized)
    optstring = _getopt_initialize (argc, argv, optstring, d, posixly_correct);
  else if (optstring[0] == '-' || optstring[0] == '+')
    optstring++;

  if (optstring[0] == ':')
    print_errors = 0;

  /* Test whether ARGV[optind] points to a non-option argument.  */
#define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

  if (d->__nextchar == NULL || *d->__nextchar == '\0')
    {
      /* Advance to the next ARGV-element.  */

      /* Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
	 moved back by the user (who may also have changed the arguments).  */
      if (d->__last_nonopt > d->optind)
	d->__last_nonopt = d->optind;
      if (d->__first_nonopt > d->optind)
	d->__first_nonopt = d->optind;

      if (d->__ordering == PERMUTE)
	{
	  /* If we have just processed some options following some non-options,
	     exchange them so that the options come first.  */

	  if (d->__first_nonopt != d->__last_nonopt
	      && d->__last_nonopt != d->optind)
	    exchange (argv, d);
	  else if (d->__last_nonopt != d->optind)
	    d->__first_nonopt = d->optind;

	  /* Skip any additional non-options
	     and extend the range of non-options previously skipped.  */

	  while (d->optind < argc && NONOPTION_P)
	    d->optind++;
	  d->__last_nonopt = d->optind;
	}

      /* The special ARGV-element '--' means premature end of options.
	 Skip it like a null option,
	 then exchange with previous non-options as if it were an option,
	 then skip everything else like a non-option.  */

      if (d->optind != argc && !strcmp (argv[d->optind], "--"))
	{
	  d->optind++;

	  if (d->__first_nonopt != d->__last_nonopt
	      && d->__last_nonopt != d->optind)
	    exchange (argv, d);
	  else if (d->__first_nonopt == d->__last_nonopt)
	    d->__first_nonopt = d->optind;
	  d->__last_nonopt = argc;

	  d->optind = argc;
	}

      /* If we have done all the ARGV-elements, stop the scan
	 and back over any non-options that we skipped and permuted.  */

      if (d->optind == argc)
	{
	  /* Set the next-arg-index to point at the non-options
	     that we previously skipped, so the caller will digest them.  */
	  if (d->__first_nonopt != d->__last_nonopt)
	    d->optind = d->__first_nonopt;
	  return -1;
	}

      /* If we have come to a non-option and did not permute it,
	 either stop the scan or describe it to the caller and pass it by.  */

      if (NONOPTION_P)
	{
	  if (d->__ordering == REQUIRE_ORDER)
	    return -1;
	  d->optarg = argv[d->optind++];
	  return 1;
	}

      /* We have found another option-ARGV-element.
	 Check whether it might be a long option.  */
      if (longopts)
	{
	  if (argv[d->optind][1] == '-')
	    {
	      /* "--foo" is always a long option.  The special option
		 "--" was handled above.  */
	      d->__nextchar = argv[d->optind] + 2;
	      return process_long_option (argc, argv, optstring, longopts,
					  longind, long_only, d,
					  print_errors, "--");
	    }

	  /* If long_only and the ARGV-element has the form "-f",
	     where f is a valid short option, don't consider it an
	     abbreviated form of a long option that starts with f.
	     Otherwise there would be no way to give the -f short
	     option.

	     On the other hand, if there's a long option "fubar" and
	     the ARGV-element is "-fu", do consider that an
	     abbreviation of the long option, just like "--fu", and
	     not "-f" with arg "u".

	     This distinction seems to be the most useful approach.  */
	  if (long_only && (argv[d->optind][2]
			    || !strchr (optstring, argv[d->optind][1])))
	    {
	      int code;
	      d->__nextchar = argv[d->optind] + 1;
	      code = process_long_option (argc, argv, optstring, longopts,
					  longind, long_only, d,
					  print_errors, "-");
	      if (code != -1)
		return code;
	    }
	}

      /* It is not a long option.  Skip the initial punctuation.  */
      d->__nextchar = argv[d->optind] + 1;
    }

  /* Look at and handle the next short option-character.  */

  {
    char c = *d->__nextchar++;
    const char *temp = strchr (optstring, c);

    /* Increment 'optind' when we start to process its last character.  */
    if (*d->__nextchar == '\0')
      ++d->optind;

    if (temp == NULL || c == ':' || c == ';')
      {
	if (print_errors)
	  fprintf (stderr, _("%s: invalid option -- '%c'\n"), argv[0], c);
	d->optopt = c;
	return '?';
      }

    /* Convenience. Treat POSIX -W foo same as long option --foo */
    if (temp[0] == 'W' && temp[1] == ';' && longopts != NULL)
      {
	/* This is an option that requires an argument.  */
	if (*d->__nextchar != '\0')
	  d->optarg = d->__nextchar;
	else if (d->optind == argc)
	  {
	    if (print_errors)
	      fprintf (stderr,
		       _("%s: option requires an argument -- '%c'\n"),
		       argv[0], c);

	    d->optopt = c;
	    if (optstring[0] == ':')
	      c = ':';
	    else
	      c = '?';
	    return c;
	  }
	else
	  d->optarg = argv[d->optind];

	d->__nextchar = d->optarg;
	d->optarg = NULL;
	return process_long_option (argc, argv, optstring, longopts, longind,
				    0 /* long_only */, d, print_errors, "-W ");
      }
    if (temp[1] == ':')
      {
	if (temp[2] == ':')
	  {
	    /* This is an option that accepts an argument optionally.  */
	    if (*d->__nextchar != '\0')
	      {
		d->optarg = d->__nextchar;
		d->optind++;
	      }
	    else
	      d->optarg = NULL;
	    d->__nextchar = NULL;
	  }
	else
	  {
	    /* This is an option that requires an argument.  */
	    if (*d->__nextchar != '\0')
	      {
		d->optarg = d->__nextchar;
		/* If we end this ARGV-element by taking the rest as an arg,
		   we must advance to the next element now.  */
		d->optind++;
	      }
	    else if (d->optind == argc)
	      {
		if (print_errors)
		  fprintf (stderr,
			   _("%s: option requires an argument -- '%c'\n"),
			   argv[0], c);

		d->optopt = c;
		if (optstring[0] == ':')
		  c = ':';
		else
		  c = '?';
	      }
	    else
	      /* We already incremented 'optind' once;
		 increment it again when taking next ARGV-elt as argument.  */
	      d->optarg = argv[d->optind++];
	    d->__nextchar = NULL;
	  }
      }
    return c;
  }
}