#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  pi ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_6__ {int /*<<< orphan*/  hThread; } ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateProcess (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

int main( int argc, char **argv ) {
  HANDLE h_process;
  HANDLE h_process_in_parent;

  fprintf( stderr, "%lu: Starting\n", GetCurrentProcessId() );

  if( argc == 2 ) {
    h_process = (HANDLE)(ULONG_PTR)atoi(argv[1]);
  } else {
    if( !DuplicateHandle( GetCurrentProcess(),
			  GetCurrentProcess(),
			  GetCurrentProcess(),
			  &h_process,
			  0,
			  TRUE,
			  DUPLICATE_SAME_ACCESS) ) {
      fprintf( stderr, "%lu: Could not duplicate my own process handle.\n",
	       GetCurrentProcessId() );
      return 101;
    }
  }

  if( argc == 1 ) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmdline[1000];

    memset( &si, 0, sizeof( si ) );
    memset( &pi, 0, sizeof( pi ) );

    sprintf( cmdline, "%s %p", argv[0], h_process );
    if( !CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL,
		       &si, &pi ) ) {
      fprintf( stderr, "%lu: Could not create child process.\n",
	       GetCurrentProcessId() );
      return 5;
    }

    if( WaitForSingleObject( pi.hThread, INFINITE ) != WAIT_OBJECT_0 ) {
      fprintf( stderr, "%lu: Failed to wait for child process to terminate.\n",
	       GetCurrentProcessId() );
      return 6;
    }
  } else {
    if( !DuplicateHandle( GetCurrentProcess(),
			  GetCurrentProcess(),
			  h_process,
			  &h_process_in_parent,
			  0,
			  TRUE,
			  DUPLICATE_SAME_ACCESS) ) {
      fprintf( stderr, "%lu: Could not duplicate my handle into the parent.\n",
	       GetCurrentProcessId() );
      return 102;
    }
  }

  return 0;
}