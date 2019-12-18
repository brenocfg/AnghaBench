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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFMAXPENDING ; 
 int MAXMAXPENDING ; 
 int OPT_DEBUG ; 
 int OPT_POLL ; 
 int /*<<< orphan*/  VERSION_MESSAGE (char*) ; 
 int /*<<< orphan*/  aargh (char*) ; 
 int atoi (char*) ; 
 char* config_text ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printhelp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proclog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[]) {
  int c, opts, maxpending;
  extern char *optarg;
  FILE *inf;

  if (argv[1] && !strncmp(argv[1],"--",2)) {
    if (!strcmp(argv[1],"--help")) {
      printhelp(stdout);
    } else if (!strcmp(argv[1],"--version")) {
      fputs(VERSION_MESSAGE("adnslogres"),stdout);
    } else {
      usage();
    }
    if (ferror(stdout) || fclose(stdout)) { perror("stdout"); exit(1); }
    exit(0);
  }

  maxpending= DEFMAXPENDING;
  opts= 0;
  while ((c= getopt(argc, argv, "c:C:dp")) != -1)
    switch (c) {
    case 'c':
      maxpending= atoi(optarg);
      if (maxpending < 1 || maxpending > MAXMAXPENDING) {
       fprintf(stderr, "%s: unfeasible concurrency %d\n", progname, maxpending);
       exit(1);
      }
      break;
    case 'C':
      config_text= optarg;
      break;
    case 'd':
      opts|= OPT_DEBUG;
      break;
#ifdef HAVE_POLL
    case 'p':
      opts|= OPT_POLL;
      break;
#endif
    default:
      usage();
    }

  argc-= optind;
  argv+= optind;

  inf= NULL;
  if (argc == 0)
    inf= stdin;
  else if (argc == 1)
    inf= fopen(*argv, "r");
  else
    usage();

  if (!inf)
    aargh("couldn't open input");

  proclog(inf, stdout, maxpending, opts);

  if (fclose(inf))
    aargh("fclose input");
  if (fclose(stdout))
    aargh("fclose output");

  return 0;
}