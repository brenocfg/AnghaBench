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
typedef  int LONG ;
typedef  int INT ;
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  FILE_END ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HFILE_ERROR ; 
 int _hread (scalar_t__,char*,int) ; 
 int _hwrite (scalar_t__,char*,int) ; 
 scalar_t__ _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _llseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* sillytext ; 
 int strlen (char*) ; 

__attribute__((used)) static void test__llseek( void )
{
    INT i;
    HFILE filehandle;
    char buffer[1];
    LONG bytes_read;
    BOOL ret;

    filehandle = _lcreat( filename, 0 );
    if (filehandle == HFILE_ERROR)
    {
        ok(0,"couldn't create file \"%s\" (err=%d)\n",filename,GetLastError());
        return;
    }

    for (i = 0; i < 400; i++)
    {
        ok( _hwrite( filehandle, sillytext, strlen( sillytext ) ) != -1, "_hwrite complains\n" );
    }
    ok( _llseek( filehandle, 400 * strlen( sillytext ), FILE_CURRENT ) != -1, "should be able to seek\n" );
    ok( _llseek( filehandle, 27 + 35 * strlen( sillytext ), FILE_BEGIN ) != -1, "should be able to seek\n" );

    bytes_read = _hread( filehandle, buffer, 1);
    ok( 1 == bytes_read, "file read size error\n" );
    ok( buffer[0] == sillytext[27], "_llseek error, it got lost seeking\n" );
    ok( _llseek( filehandle, -400 * (LONG)strlen( sillytext ), FILE_END ) != -1, "should be able to seek\n" );

    bytes_read = _hread( filehandle, buffer, 1);
    ok( 1 == bytes_read, "file read size error\n" );
    ok( buffer[0] == sillytext[0], "_llseek error, it got lost seeking\n" );
    ok( _llseek( filehandle, 1000000, FILE_END ) != -1, "should be able to seek past file; poor, poor Windows programmers\n" );
    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    ret = DeleteFileA( filename );
    ok( ret, "DeleteFile failed (%d)\n", GetLastError(  ) );
}