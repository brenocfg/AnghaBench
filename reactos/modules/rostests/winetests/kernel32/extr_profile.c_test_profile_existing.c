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
typedef  int /*<<< orphan*/  pe ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int const,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
#define  ERROR_SHARING_VIOLATION 134 
#define  FALSE 133 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
#define  FILE_SHARE_READ 132 
#define  FILE_SHARE_WRITE 131 
#define  GENERIC_READ 130 
#define  GENERIC_WRITE 129 
 int GetLastError () ; 
 int GetPrivateProfileStringA (char*,char*,int /*<<< orphan*/ *,char*,int,char const*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 char* KEY ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 char* SECTION ; 
 int /*<<< orphan*/  SetLastError (int) ; 
#define  TRUE 128 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int WritePrivateProfileStringA (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_profile_existing(void)
{
    static const char *testfile1 = ".\\winesharing1.ini";
    static const char *testfile2 = ".\\winesharing2.ini";

    static const struct {
        DWORD dwDesiredAccess;
        DWORD dwShareMode;
        DWORD write_error;
        BOOL read_error;
        DWORD broken_error;
    } pe[] = {
        {GENERIC_READ,  FILE_SHARE_READ,  ERROR_SHARING_VIOLATION, FALSE },
        {GENERIC_READ,  FILE_SHARE_WRITE, ERROR_SHARING_VIOLATION, TRUE },
        {GENERIC_WRITE, FILE_SHARE_READ,  ERROR_SHARING_VIOLATION, FALSE },
        {GENERIC_WRITE, FILE_SHARE_WRITE, ERROR_SHARING_VIOLATION, TRUE },
        {GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ,  ERROR_SHARING_VIOLATION, FALSE },
        {GENERIC_READ|GENERIC_WRITE, FILE_SHARE_WRITE, ERROR_SHARING_VIOLATION, TRUE },
        {GENERIC_READ,  FILE_SHARE_READ|FILE_SHARE_WRITE, 0, FALSE, ERROR_SHARING_VIOLATION /* nt4 */},
        {GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, FALSE, ERROR_SHARING_VIOLATION /* nt4 */},
        /*Thief demo (bug 5024) opens .ini file like this*/
        {GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, FALSE, ERROR_SHARING_VIOLATION /* nt4 */}
    };

    int i;
    BOOL ret;
    DWORD size;
    HANDLE h = 0;
    char buffer[MAX_PATH];

    for (i=0; i < sizeof(pe)/sizeof(pe[0]); i++)
    {
        h = CreateFileA(testfile1, pe[i].dwDesiredAccess, pe[i].dwShareMode, NULL,
                       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        ok(INVALID_HANDLE_VALUE != h, "%d: CreateFile failed\n",i);
        SetLastError(0xdeadbeef);

        ret = WritePrivateProfileStringA(SECTION, KEY, "12345", testfile1);
        if (!pe[i].write_error)
        {
            if (!ret)
                ok( broken(GetLastError() == pe[i].broken_error),
                    "%d: WritePrivateProfileString failed with error %u\n", i, GetLastError() );
            CloseHandle(h);
            size = GetPrivateProfileStringA(SECTION, KEY, 0, buffer, MAX_PATH, testfile1);
            if (ret)
                ok( size == 5, "%d: test failed, number of characters copied: %d instead of 5\n", i, size );
            else
                ok( !size, "%d: test failed, number of characters copied: %d instead of 0\n", i, size );
        }
        else
        {
            DWORD err = GetLastError();
            ok( !ret, "%d: WritePrivateProfileString succeeded\n", i );
            if (!ret)
                ok( err == pe[i].write_error, "%d: WritePrivateProfileString failed with error %u/%u\n",
                    i, err, pe[i].write_error );
            CloseHandle(h);
            size = GetPrivateProfileStringA(SECTION, KEY, 0, buffer, MAX_PATH, testfile1);
            ok( !size, "%d: test failed, number of characters copied: %d instead of 0\n", i, size );
        }

        ok( DeleteFileA(testfile1), "delete failed\n" );
    }

    h = CreateFileA(testfile2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    sprintf( buffer, "[%s]\r\n%s=123\r\n", SECTION, KEY );
    ok( WriteFile( h, buffer, strlen(buffer), &size, NULL ), "failed to write\n" );
    CloseHandle( h );

    for (i=0; i < sizeof(pe)/sizeof(pe[0]); i++)
    {
        h = CreateFileA(testfile2, pe[i].dwDesiredAccess, pe[i].dwShareMode, NULL,
                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        ok(INVALID_HANDLE_VALUE != h, "%d: CreateFile failed\n",i);
        SetLastError(0xdeadbeef);
        ret = GetPrivateProfileStringA(SECTION, KEY, NULL, buffer, MAX_PATH, testfile2);
        /* Win9x and WinME returns 0 for all cases except the first one */
        if (!pe[i].read_error)
            ok( ret ||
                broken(!ret && GetLastError() == 0xdeadbeef), /* Win9x, WinME */
                "%d: GetPrivateProfileString failed with error %u\n", i, GetLastError() );
        else
            ok( !ret, "%d: GetPrivateProfileString succeeded\n", i );
        CloseHandle(h);
    }
    ok( DeleteFileA(testfile2), "delete failed\n" );
}