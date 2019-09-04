#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startup ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_9__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_8__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
struct TYPE_7__ {int cb; void* hStdError; void* hStdOutput; int /*<<< orphan*/  hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int CREATE_DEFAULT_ERROR_MODE ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int NORMAL_PRIORITY_CLASS ; 
 scalar_t__ RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenCurrentUser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  p_fopen_s ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_invalid_stdin( const char* selfname )
{
    char cmdline[MAX_PATH];
    PROCESS_INFORMATION proc;
    SECURITY_ATTRIBUTES sa;
    STARTUPINFOA startup;
    HKEY key;
    LONG ret;

    if(!p_fopen_s) {
        /* Behaviour of the dll has changed in newer version */
        win_skip("skipping invalid stdin tests\n");
        return;
    }

    ret = RegOpenCurrentUser(KEY_READ, &key);
    ok(!ret, "RegOpenCurrentUser failed: %x\n", ret);

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = key;
    startup.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    startup.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    sprintf(cmdline, "%s file stdin", selfname);
    CreateProcessA(NULL, cmdline, NULL, NULL, TRUE,
            CREATE_DEFAULT_ERROR_MODE|NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &proc);
    winetest_wait_child_process(proc.hProcess);

    ret = RegCloseKey(key);
    ok(!ret, "RegCloseKey failed: %x\n", ret);
}