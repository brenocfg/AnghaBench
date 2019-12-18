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
struct MY_STAT {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Char ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  MY_STAT (char*,struct MY_STAT*) ; 
 scalar_t__ MY_S_ISDIR (int /*<<< orphan*/ ) ; 
#define  SM_F2F 130 
#define  SM_F2O 129 
#define  SM_I2O 128 
 int /*<<< orphan*/  True ; 
 scalar_t__ containsDubiousChars (char*) ; 
 int /*<<< orphan*/  copyFileName (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleteOutputOnInterrupt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileExists (char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* inName ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ noisy ; 
 char* outName ; 
 int /*<<< orphan*/ * outputHandleJustInCase ; 
 int /*<<< orphan*/  pad (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 char* progName ; 
 int /*<<< orphan*/  setExit (int) ; 
 int srcMode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testFailsExist ; 
 scalar_t__ testStream (int /*<<< orphan*/ *) ; 
 int verbosity ; 

__attribute__((used)) static 
void testf ( Char *name )
{
   FILE *inStr;
   Bool allOK;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = False;

   if (name == NULL && srcMode != SM_I2O)
      panic ( "testf: bad modes\n" );

   copyFileName ( outName, (Char*)"(none)" );
   switch (srcMode) {
      case SM_I2O: copyFileName ( inName, (Char*)"(stdin)" ); break;
      case SM_F2F: copyFileName ( inName, name ); break;
      case SM_F2O: copyFileName ( inName, name ); break;
   }

   if ( srcMode != SM_I2O && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != SM_I2O && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   if ( srcMode != SM_I2O ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }

   switch ( srcMode ) {

      case SM_I2O:
         if ( isatty ( fileno ( stdin ) ) ) {
            fprintf ( stderr,
                      "%s: I won't read compressed data from a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         inStr = stdin;
         break;

      case SM_F2O: case SM_F2F:
         inStr = fopen ( inName, "rb" );
         if ( inStr == NULL ) {
            fprintf ( stderr, "%s: Can't open input file %s:%s.\n",
                      progName, inName, strerror(errno) );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "testf: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr, "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }

   /*--- Now the input handle is sane.  Do the Biz. ---*/
   outputHandleJustInCase = NULL;
   allOK = testStream ( inStr );

   if (allOK && verbosity >= 1) fprintf ( stderr, "ok\n" );
   if (!allOK) testFailsExist = True;
}