#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eType; int /*<<< orphan*/  zHelp; scalar_t__ zText; } ;
typedef  TYPE_1__ CmdLineOption ;

/* Variables and functions */
 int CMDLINE_BARE ; 
 int CMDLINE_BOOLEAN ; 
 int CMDLINE_INTEGER ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void unknown_option_error(
  const char *zArg, 
  CmdLineOption *aOpt,
  const char *zHelp
){
  int i;
  fprintf(stderr, "Unknown option: %s\n", zArg);
  fprintf(stderr, "\nOptions are:\n");
  fprintf(stderr, "  % -30sEcho command line options\n", "-cmdline:verbose");
  for(i=0; aOpt[i].zText; i++){
    int eType = aOpt[i].eType;
    char *zOpt = sqlite3_mprintf("%s %s", aOpt[i].zText,
        eType==CMDLINE_BARE ? "" :
        eType==CMDLINE_INTEGER ? "N" :
        eType==CMDLINE_BOOLEAN ? "BOOLEAN" : "TEXT"
    );
    fprintf(stderr, "  % -30s%s\n", zOpt, aOpt[i].zHelp);
    sqlite3_free(zOpt);
  }
  if( zHelp ){
    fprintf(stderr, "\n%s\n", zHelp);
  }
  exit(1);
}