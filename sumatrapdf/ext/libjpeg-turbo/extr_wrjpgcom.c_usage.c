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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ MAX_COM_LENGTH ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage (void)
/* complain about bad command line */
{
  fprintf(stderr, "wrjpgcom inserts a textual comment in a JPEG file.\n");
  fprintf(stderr, "You can add to or replace any existing comment(s).\n");

  fprintf(stderr, "Usage: %s [switches] ", progname);
#ifdef TWO_FILE_COMMANDLINE
  fprintf(stderr, "inputfile outputfile\n");
#else
  fprintf(stderr, "[inputfile]\n");
#endif

  fprintf(stderr, "Switches (names may be abbreviated):\n");
  fprintf(stderr, "  -replace         Delete any existing comments\n");
  fprintf(stderr, "  -comment \"text\"  Insert comment with given text\n");
  fprintf(stderr, "  -cfile name      Read comment from named file\n");
  fprintf(stderr, "Notice that you must put quotes around the comment text\n");
  fprintf(stderr, "when you use -comment.\n");
  fprintf(stderr, "If you do not give either -comment or -cfile on the command line,\n");
  fprintf(stderr, "then the comment text is read from standard input.\n");
  fprintf(stderr, "It can be multiple lines, up to %u characters total.\n",
	  (unsigned int) MAX_COM_LENGTH);
#ifndef TWO_FILE_COMMANDLINE
  fprintf(stderr, "You must specify an input JPEG file name when supplying\n");
  fprintf(stderr, "comment text from standard input.\n");
#endif

  exit(EXIT_FAILURE);
}