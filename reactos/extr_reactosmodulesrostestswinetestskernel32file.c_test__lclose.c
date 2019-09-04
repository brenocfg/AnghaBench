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
typedef  scalar_t__ HFILE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HFILE_ERROR ; 
 scalar_t__ _hwrite (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sillytext ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test__lclose( void )
{
    HFILE filehandle;
    BOOL ret;

    filehandle = _lcreat( filename, 0 );
    if (filehandle == HFILE_ERROR)
    {
        ok(0,"couldn't create file \"%s\" (err=%d)\n",filename,GetLastError());
        return;
    }

    ok( HFILE_ERROR != _hwrite( filehandle, sillytext, strlen( sillytext ) ), "_hwrite complains\n" );

    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    ret = DeleteFileA( filename );
    ok( ret != 0, "DeleteFile failed (%d)\n", GetLastError(  ) );
}