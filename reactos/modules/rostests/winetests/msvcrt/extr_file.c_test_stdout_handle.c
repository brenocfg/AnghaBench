#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa ;
struct TYPE_10__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_9__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
struct TYPE_8__ {void* hStdError; scalar_t__ hStdOutput; void* hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int CREATE_DEFAULT_ERROR_MODE ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 int NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 char* read_file (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_stdout_handle( STARTUPINFOA *startup, char *cmdline, HANDLE hstdout, BOOL expect_stdout,
                                const char *descr )
{
    const char *data;
    HANDLE hErrorFile;
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION proc;

    /* make file handle inheritable */
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    hErrorFile = CreateFileA( "fdopen.err", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    startup->dwFlags    = STARTF_USESTDHANDLES;
    startup->hStdInput  = GetStdHandle( STD_INPUT_HANDLE );
    startup->hStdOutput = hErrorFile;
    startup->hStdError  = GetStdHandle( STD_ERROR_HANDLE );

    CreateProcessA( NULL, cmdline, NULL, NULL, TRUE,
                    CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS, NULL, NULL, startup, &proc );
    winetest_wait_child_process( proc.hProcess );

    data = read_file( hErrorFile );
    if (expect_stdout)
        ok( strcmp( data, "Success" ), "%s: Error file shouldn't contain data\n", descr );
    else
        ok( !strcmp( data, "Success" ), "%s: Wrong error data (%s)\n", descr, data );

    if (hstdout)
    {
        data = read_file( hstdout );
        if (expect_stdout)
            ok( !strcmp( data, "Success" ), "%s: Wrong stdout data (%s)\n", descr, data );
        else
            ok( strcmp( data, "Success" ), "%s: Stdout file shouldn't contain data\n", descr );
    }

    CloseHandle( hErrorFile );
    DeleteFileA( "fdopen.err" );
}