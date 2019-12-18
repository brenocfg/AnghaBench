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
 int /*<<< orphan*/  AbbrevStr (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UNAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* gLibNcFTPVersion ; 
 char* gVersion ; 
 int /*<<< orphan*/ * stderr ; 

__attribute__((used)) static void
Usage(void)
{
	FILE *fp;
#ifdef UNAME
	char s[80];
#endif

	fp = stderr;
	(void) fprintf(fp, "\nUsage:  ncftp [flags] [<host> | <directory URL to browse>]\n");
	(void) fprintf(fp, "\nFlags:\n\
  -u XX  Use username XX instead of anonymous.\n\
  -p XX  Use password XX with the username.\n\
  -P XX  Use port number XX instead of the default FTP service port (21).\n\
  -j XX  Use account XX with the username (rarely needed).\n\
  -F     Dump a sample $HOME/.ncftp/firewall prefs file to stdout and exit.\n");

	(void) fprintf(fp, "\nProgram version:  %s\nLibrary version:  %s\n", gVersion + 5, gLibNcFTPVersion + 5);
#ifdef UNAME
	AbbrevStr(s, UNAME, 60, 1);
	(void) fprintf(fp, "System:           %s\n", s);
#endif
	(void) fprintf(fp, "\nThis is a freeware program by Mike Gleason (ncftp@ncftp.com).\n");
	(void) fprintf(fp, "Use ncftpget and ncftpput for command-line FTP.\n\n");
	exit(2);
}