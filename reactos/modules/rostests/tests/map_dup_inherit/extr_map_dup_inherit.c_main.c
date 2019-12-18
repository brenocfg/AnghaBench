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
struct TYPE_6__ {void* hProcess; int /*<<< orphan*/  hThread; } ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateFileMapping (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcess (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FILE_MAP_WRITE ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 int /*<<< orphan*/  INFINITE ; 
 void* INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 scalar_t__ MapViewOfFile (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int PAGE_READWRITE ; 
 int SEC_RESERVE ; 
 int /*<<< orphan*/  SetHandleInformation (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UlongToPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualAlloc (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _atoi64 (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,void*) ; 
 int /*<<< orphan*/  stderr ; 

int main( int argc, char **argv ) {
  HANDLE file_view;
  void *file_map;
  int *x;

  fprintf( stderr, "%lu: Starting\n", GetCurrentProcessId() );

  if( argc == 2 ) {
    #ifdef WIN64
        file_map = (void *)_atoi64(argv[1]);
    #else
        file_map = (void *)UlongToPtr(atoi(argv[1]));
    #endif
  } else {
    file_map = CreateFileMapping( INVALID_HANDLE_VALUE,
				  NULL,
				  PAGE_READWRITE | SEC_RESERVE,
				  0, 0x1000, NULL );
    if( !SetHandleInformation( file_map,
			       HANDLE_FLAG_INHERIT,
			       HANDLE_FLAG_INHERIT ) ) {
      fprintf( stderr, "%lu: Could not make handle inheritable.\n",
	       GetCurrentProcessId() );
      return 100;
    }
  }

  if( !file_map ) {
    fprintf( stderr, "%lu: Could not create anonymous file map.\n",
	     GetCurrentProcessId() );
    return 1;
  }

  file_view = MapViewOfFile( file_map,
			     FILE_MAP_WRITE,
			     0,
			     0,
			     0x1000 );

  if( !file_view ) {
    fprintf( stderr, "%lu: Could not map view of file.\n",
	     GetCurrentProcessId() );
    if (file_map != INVALID_HANDLE_VALUE)
        CloseHandle(file_map);
    return 2;
  }

  if( !VirtualAlloc( file_view, 0x1000, MEM_COMMIT, PAGE_READWRITE ) ) {
    fprintf( stderr, "%lu: VirtualAlloc failed to realize the page.\n",
	     GetCurrentProcessId() );
    if (file_map != INVALID_HANDLE_VALUE)
        CloseHandle(file_map);
    return 3;
  }

  x = (int *)file_view;
  x[0] = 0x12345678;

  if( x[0] != 0x12345678 ) {
    fprintf( stderr, "%lu: Can't write to the memory (%08x != 0x12345678)\n",
	     GetCurrentProcessId(), x[0] );
    return 4;
  }

  if( argc == 1 ) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmdline[1000];

    memset( &si, 0, sizeof( si ) );
    memset( &pi, 0, sizeof( pi ) );

    sprintf(cmdline,"%s %p", argv[0], file_map);
	CloseHandle(file_map);

    if( !CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL,
		       &si, &pi ) ) {
      fprintf( stderr, "%lu: Could not create child process.\n",
	       GetCurrentProcessId() );
      if (pi.hProcess != INVALID_HANDLE_VALUE)
          CloseHandle(pi.hProcess);

      return 5;
    }

    if( WaitForSingleObject( pi.hThread, INFINITE ) != WAIT_OBJECT_0 ) {
      fprintf( stderr, "%lu: Failed to wait for child process to terminate.\n",
	       GetCurrentProcessId() );
      if (pi.hProcess != INVALID_HANDLE_VALUE)
          CloseHandle(pi.hProcess);
      return 6;
    }

    if (pi.hProcess != INVALID_HANDLE_VALUE)
        CloseHandle(pi.hProcess);

  }

  return 0;
}