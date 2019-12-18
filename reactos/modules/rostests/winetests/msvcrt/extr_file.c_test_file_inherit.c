#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startup ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_8__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
struct TYPE_7__ {int cb; int cbReserved2; scalar_t__ lpReserved2; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_NOINHERIT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _P_WAIT ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  _spawnvp (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  create_io_inherit_block (TYPE_1__*,int,scalar_t__*) ; 
 char* get_base_name (char const*) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int open (char*,int,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int tell (int) ; 
 int /*<<< orphan*/  test_stdout_handle (TYPE_1__*,char*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void test_file_inherit( const char* selfname )
{
    int			fd;
    const char*		arg_v[5];
    char 		buffer[16];
    char cmdline[MAX_PATH];
    STARTUPINFOA startup;
    SECURITY_ATTRIBUTES sa;
    HANDLE handles[3];

    fd = open ("fdopen.tst", O_CREAT | O_RDWR | O_BINARY, _S_IREAD |_S_IWRITE);
    ok(fd != -1, "Couldn't create test file\n");
    arg_v[0] = get_base_name(selfname);
    arg_v[1] = "tests/file.c";
    arg_v[2] = "inherit";
    arg_v[3] = buffer; sprintf(buffer, "%d", fd);
    arg_v[4] = 0;
    _spawnvp(_P_WAIT, selfname, arg_v);
    ok(tell(fd) == 8, "bad position %u expecting 8\n", tell(fd));
    lseek(fd, 0, SEEK_SET);
    ok(read(fd, buffer, sizeof (buffer)) == 8 && memcmp(buffer, "Success", 8) == 0, "Couldn't read back the data\n");
    close (fd);
    ok(unlink("fdopen.tst") == 0, "Couldn't unlink\n");
    
    fd = open ("fdopen.tst", O_CREAT | O_RDWR | O_BINARY | O_NOINHERIT, _S_IREAD |_S_IWRITE);
    ok(fd != -1, "Couldn't create test file\n");
    arg_v[1] = "tests/file.c";
    arg_v[2] = "inherit_no";
    arg_v[3] = buffer; sprintf(buffer, "%d", fd);
    arg_v[4] = 0;
    _spawnvp(_P_WAIT, selfname, arg_v);
    ok(tell(fd) == 0, "bad position %u expecting 0\n", tell(fd));
    ok(read(fd, buffer, sizeof (buffer)) == 0, "Found unexpected data (%s)\n", buffer);
    close (fd);
    ok(unlink("fdopen.tst") == 0, "Couldn't unlink\n");

    /* make file handle inheritable */
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    sprintf(cmdline, "%s file inherit 1", selfname);

    /* init an empty Reserved2, which should not be recognized as inherit-block */
    ZeroMemory(&startup, sizeof(startup));
    startup.cb = sizeof(startup);
    create_io_inherit_block( &startup, 0, NULL );
    test_stdout_handle( &startup, cmdline, 0, FALSE, "empty block" );

    /* test with valid inheritblock */
    handles[0] = GetStdHandle( STD_INPUT_HANDLE );
    handles[1] = CreateFileA( "fdopen.tst", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    handles[2] = GetStdHandle( STD_ERROR_HANDLE );
    create_io_inherit_block( &startup, 3, handles );
    test_stdout_handle( &startup, cmdline, handles[1], TRUE, "valid block" );
    CloseHandle( handles[1] );
    DeleteFileA("fdopen.tst");

    /* test inherit block starting with unsigned zero */
    handles[1] = CreateFileA( "fdopen.tst", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    create_io_inherit_block( &startup, 3, handles );
    *(unsigned int *)startup.lpReserved2 = 0;
    test_stdout_handle( &startup, cmdline, handles[1], FALSE, "zero count block" );
    CloseHandle( handles[1] );
    DeleteFileA("fdopen.tst");

    /* test inherit block with smaller size */
    handles[1] = CreateFileA( "fdopen.tst", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    create_io_inherit_block( &startup, 3, handles );
    startup.cbReserved2 -= 3;
    test_stdout_handle( &startup, cmdline, handles[1], TRUE, "small size block" );
    CloseHandle( handles[1] );
    DeleteFileA("fdopen.tst");

    /* test inherit block with even smaller size */
    handles[1] = CreateFileA( "fdopen.tst", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    create_io_inherit_block( &startup, 3, handles );
    startup.cbReserved2 = sizeof(unsigned int) + sizeof(HANDLE) + sizeof(char);
    test_stdout_handle( &startup, cmdline, handles[1], FALSE, "smaller size block" );
    CloseHandle( handles[1] );
    DeleteFileA("fdopen.tst");

    /* test inherit block with larger size */
    handles[1] = CreateFileA( "fdopen.tst", GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, 0, NULL );
    create_io_inherit_block( &startup, 3, handles );
    startup.cbReserved2 += 7;
    test_stdout_handle( &startup, cmdline, handles[1], TRUE, "large size block" );
    CloseHandle( handles[1] );
    DeleteFileA("fdopen.tst");
}