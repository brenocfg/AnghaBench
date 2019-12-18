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
typedef  int UINT ;
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  OF_READWRITE ; 
 int /*<<< orphan*/  OF_WRITE ; 
 scalar_t__ _hread (scalar_t__,char*,int) ; 
 scalar_t__ _hwrite (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sillytext ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test__llopen( void )
{
    HFILE filehandle;
    UINT bytes_read;
    char buffer[10000];
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
    ok( HFILE_ERROR == _hwrite( filehandle, sillytext, strlen( sillytext ) ), "_hwrite shouldn't be able to write!\n" );
    bytes_read = _hread( filehandle, buffer, strlen( sillytext ) );
    ok( strlen( sillytext )  == bytes_read, "file read size error\n" );
    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    filehandle = _lopen( filename, OF_READWRITE );
    bytes_read = _hread( filehandle, buffer, 2 * strlen( sillytext ) );
    ok( strlen( sillytext )  == bytes_read, "file read size error\n" );
    ok( HFILE_ERROR != _hwrite( filehandle, sillytext, strlen( sillytext ) ), "_hwrite should write just fine\n" );
    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    filehandle = _lopen( filename, OF_WRITE );
    ok( HFILE_ERROR == _hread( filehandle, buffer, 1 ), "you should only be able to write this file\n" );
    ok( HFILE_ERROR != _hwrite( filehandle, sillytext, strlen( sillytext ) ), "_hwrite should write just fine\n" );
    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    ret = DeleteFileA( filename );
    ok( ret, "DeleteFile failed (%d)\n", GetLastError(  ) );
    /* TODO - add tests for the SHARE modes  -  use two processes to pull this one off */
}