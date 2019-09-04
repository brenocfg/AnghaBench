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
 int /*<<< orphan*/  VERSION_PRINT_QUIT (char*) ; 
 int address ; 
 int /*<<< orphan*/  adns_if_debug ; 
 int /*<<< orphan*/  adns_r_ptr_raw ; 
 int bracket ; 
 char const* config_text ; 
 int forever ; 
 int /*<<< orphan*/  initflags ; 
 int /*<<< orphan*/  quitnow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrt ; 
 int /*<<< orphan*/  settimeout (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  usageerr (char*) ; 

__attribute__((used)) static void parseargs(const char *const *argv) {
  const char *arg;
  int c;

  while ((arg= *++argv)) {
    if (arg[0] != '-') usageerr("no non-option arguments are allowed");
    if (arg[1] == '-') {
      if (!strcmp(arg,"--timeout")) {
	if (!(arg= *++argv)) usageerr("--timeout needs a value");
	settimeout(arg);
	forever= 0;
      } else if (!strcmp(arg,"--wait")) {
	forever= 1;
      } else if (!strcmp(arg,"--brackets")) {
	bracket= 1;
      } else if (!strcmp(arg,"--address")) {
	address= 1;
      } else if (!strcmp(arg,"--unchecked")) {
	rrt= adns_r_ptr_raw;
      } else if (!strcmp(arg,"--config")) {
	if (!(arg= *++argv)) usageerr("--config needs a value");
	config_text= arg;
      } else if (!strcmp(arg,"--debug")) {
	initflags |= adns_if_debug;
      } else if (!strcmp(arg,"--help")) {
	usage(); quitnow(0);
      } else if (!strcmp(arg,"--version")) {
	VERSION_PRINT_QUIT("adnsresfilter"); quitnow(0);
      } else {
	usageerr("unknown long option");
      }
    } else {
      while ((c= *++arg)) {
	switch (c) {
	case 't':
	  if (*++arg) settimeout(arg);
	  else if ((arg= *++argv)) settimeout(arg);
	  else usageerr("-t needs a value");
	  forever= 0;
	  arg= "\0";
	  break;
	case 'w':
	  forever= 1;
	  break;
	case 'b':
	  bracket= 1;
	  break;
	case 'a':
	  address= 1;
	  break;
	case 'u':
	  rrt= adns_r_ptr_raw;
	  break;
	case 'h':
	  usage();
	  quitnow(0);
	default:
	  usageerr("unknown short option");
	}
      }
    }
  }
}