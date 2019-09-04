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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  OF_READ ; 
 scalar_t__ _hwrite (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _llseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lread (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* sillytext ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void test__lread( void )
{
    HFILE filehandle;
    char buffer[10000];
    UINT bytes_read;
    UINT bytes_wanted;
    UINT i;
    BOOL ret;

    filehandle = _lcreat( filename, 0 );
    if (filehandle == HFILE_ERROR)
    {
        ok(0,"couldn't create file \"%s\" (err=%d)\n",filename,GetLastError());
        return;
    }

    ok( HFILE_ERROR != _hwrite( filehandle, sillytext, strlen( sillytext ) ), "_hwrite complains\n" );

    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    filehandle = _lopen( filename, OF_READ );

    ok( HFILE_ERROR != filehandle, "couldn't open file \"%s\" again (err=%d)\n", filename, GetLastError());

    bytes_read = _lread( filehandle, buffer, 2 * strlen( sillytext ) );

    ok( lstrlenA( sillytext ) == bytes_read, "file read size error\n" );

    for (bytes_wanted = 0; bytes_wanted < strlen( sillytext ); bytes_wanted++)
    {
        ok( 0 == _llseek( filehandle, 0, FILE_BEGIN ), "_llseek complains\n" );
        ok( _lread( filehandle, buffer, bytes_wanted ) == bytes_wanted, "erratic _hread return value\n" );
        for (i = 0; i < bytes_wanted; i++)
        {
            ok( buffer[i] == sillytext[i], "that's not what's written\n" );
        }
    }

    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    ret = DeleteFileA( filename );
    ok( ret, "DeleteFile failed (%d)\n", GetLastError(  ) );
}