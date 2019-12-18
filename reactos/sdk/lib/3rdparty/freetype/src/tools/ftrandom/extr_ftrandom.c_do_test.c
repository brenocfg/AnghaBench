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
 int /*<<< orphan*/  ExecuteTest (char*) ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  abort_test ; 
 int /*<<< orphan*/  alarm (int) ; 
 int child_pid ; 
 scalar_t__ copyfont (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcnt ; 
 int /*<<< orphan*/ * fontlist ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getRandom (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* results_dir ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  do_test( void )
  {
    int         i        = getRandom( 0, (int)( fcnt - 1 ) );
    static int  test_num = 0;
    char        buffer[1024];


    sprintf( buffer, "%s/test%d", results_dir, test_num++ );

    if ( copyfont ( &fontlist[i], buffer ) )
    {
      signal( SIGALRM, abort_test );
      /* Anything that takes more than 20 seconds */
      /* to parse and/or rasterize is an error.   */
      alarm( 20 );
      if ( ( child_pid = fork() ) == 0 )
        ExecuteTest( buffer );
      else if ( child_pid != -1 )
      {
        int  status;


        waitpid( child_pid, &status, 0 );
        alarm( 0 );
        if ( WIFSIGNALED ( status ) )
          printf( "Error found in file `%s'\n", buffer );
        else
          unlink( buffer );
      }
      else
      {
        fprintf( stderr, "Can't fork test case.\n" );
        exit( 1 );
      }
      alarm( 0 );
    }
  }