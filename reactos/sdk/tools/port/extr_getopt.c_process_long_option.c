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
struct option {char* name; int has_arg; scalar_t__* flag; scalar_t__ val; } ;
struct _getopt_data {char* __nextchar; size_t optind; scalar_t__ optopt; char* optarg; } ;

/* Variables and functions */
 char* _ (char*) ; 
 scalar_t__ __libc_use_alloca (int) ; 
 unsigned char* alloca (int) ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ ) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 

__attribute__((used)) static int
process_long_option (int argc, char **argv, const char *optstring,
		     const struct option *longopts, int *longind,
		     int long_only, struct _getopt_data *d,
		     int print_errors, const char *prefix)
{
  char *nameend;
  size_t namelen;
  const struct option *p;
  const struct option *pfound = NULL;
  int n_options;
  int option_index;

  for (nameend = d->__nextchar; *nameend && *nameend != '='; nameend++)
    /* Do nothing.  */ ;
  namelen = nameend - d->__nextchar;

  /* First look for an exact match, counting the options as a side
     effect.  */
  for (p = longopts, n_options = 0; p->name; p++, n_options++)
    if (!strncmp (p->name, d->__nextchar, namelen)
	&& namelen == strlen (p->name))
      {
	/* Exact match found.  */
	pfound = p;
	option_index = n_options;
	break;
      }

  if (pfound == NULL)
    {
      /* Didn't find an exact match, so look for abbreviations.  */
      unsigned char *ambig_set = NULL;
      int ambig_malloced = 0;
      int ambig_fallback = 0;
      int indfound = -1;

      for (p = longopts, option_index = 0; p->name; p++, option_index++)
	if (!strncmp (p->name, d->__nextchar, namelen))
	  {
	    if (pfound == NULL)
	      {
		/* First nonexact match found.  */
		pfound = p;
		indfound = option_index;
	      }
	    else if (long_only
		     || pfound->has_arg != p->has_arg
		     || pfound->flag != p->flag
		     || pfound->val != p->val)
	      {
		/* Second or later nonexact match found.  */
		if (!ambig_fallback)
		  {
		    if (!print_errors)
		      /* Don't waste effort tracking the ambig set if
			 we're not going to print it anyway.  */
		      ambig_fallback = 1;
		    else if (!ambig_set)
		      {
			if (__libc_use_alloca (n_options))
			  ambig_set = alloca (n_options);
			else if ((ambig_set = malloc (n_options)) == NULL)
			  /* Fall back to simpler error message.  */
			  ambig_fallback = 1;
			else
			  ambig_malloced = 1;

			if (ambig_set)
			  {
			    memset (ambig_set, 0, n_options);
			    ambig_set[indfound] = 1;
			  }
		      }
		    if (ambig_set)
		      ambig_set[option_index] = 1;
		  }
	      }
	  }

      if (ambig_set || ambig_fallback)
	{
	  if (print_errors)
	    {
	      if (ambig_fallback)
		fprintf (stderr, _("%s: option '%s%s' is ambiguous\n"),
			 argv[0], prefix, d->__nextchar);
	      else
		{
		  flockfile (stderr);
		  fprintf (stderr,
			   _("%s: option '%s%s' is ambiguous; possibilities:"),
			   argv[0], prefix, d->__nextchar);

		  for (option_index = 0; option_index < n_options; option_index++)
		    if (ambig_set[option_index])
		      fprintf (stderr, " '%s%s'",
			       prefix, longopts[option_index].name);

		  /* This must use 'fprintf' even though it's only
		     printing a single character, so that it goes through
		     __fxprintf_nocancel when compiled as part of glibc.  */
		  fprintf (stderr, "\n");
		  funlockfile (stderr);
		}
	    }
	  if (ambig_malloced)
	    free (ambig_set);
	  d->__nextchar += strlen (d->__nextchar);
	  d->optind++;
	  d->optopt = 0;
	  return '?';
	}

      option_index = indfound;
    }

  if (pfound == NULL)
    {
      /* Can't find it as a long option.  If this is not getopt_long_only,
	 or the option starts with '--' or is not a valid short option,
	 then it's an error.  */
      if (!long_only || argv[d->optind][1] == '-'
	  || strchr (optstring, *d->__nextchar) == NULL)
	{
	  if (print_errors)
	    fprintf (stderr, _("%s: unrecognized option '%s%s'\n"),
		     argv[0], prefix, d->__nextchar);

	  d->__nextchar = NULL;
	  d->optind++;
	  d->optopt = 0;
	  return '?';
	}

      /* Otherwise interpret it as a short option.  */
      return -1;
    }

  /* We have found a matching long option.  Consume it.  */
  d->optind++;
  d->__nextchar = NULL;
  if (*nameend)
    {
      /* Don't test has_arg with >, because some C compilers don't
	 allow it to be used on enums.  */
      if (pfound->has_arg)
	d->optarg = nameend + 1;
      else
	{
	  if (print_errors)
	    fprintf (stderr,
		     _("%s: option '%s%s' doesn't allow an argument\n"),
		     argv[0], prefix, pfound->name);

	  d->optopt = pfound->val;
	  return '?';
	}
    }
  else if (pfound->has_arg == 1)
    {
      if (d->optind < argc)
	d->optarg = argv[d->optind++];
      else
	{
	  if (print_errors)
	    fprintf (stderr,
		     _("%s: option '%s%s' requires an argument\n"),
		     argv[0], prefix, pfound->name);

	  d->optopt = pfound->val;
	  return optstring[0] == ':' ? ':' : '?';
	}
    }

  if (longind != NULL)
    *longind = option_index;
  if (pfound->flag)
    {
      *(pfound->flag) = pfound->val;
      return 0;
    }
  return pfound->val;
}