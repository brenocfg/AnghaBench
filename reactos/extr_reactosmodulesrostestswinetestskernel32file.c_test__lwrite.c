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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ UINT ;
typedef  size_t INT ;
typedef  scalar_t__ HLOCAL ;
typedef  scalar_t__ HFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 char* LocalLock (scalar_t__) ; 
 int /*<<< orphan*/  OF_READ ; 
 int /*<<< orphan*/  OF_READWRITE ; 
 scalar_t__ _hread (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ _lclose (scalar_t__) ; 
 scalar_t__ _lcreat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _lwrite (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test__lwrite( void )
{
    HFILE filehandle;
    char buffer[10000];
    UINT bytes_read;
    UINT bytes_written;
    UINT blocks;
    INT i;
    char *contents;
    HLOCAL memory_object;
    char checksum[1];
    BOOL ret;

    filehandle = _lcreat( filename, 0 );
    if (filehandle == HFILE_ERROR)
    {
        ok(0,"couldn't create file \"%s\" (err=%d)\n",filename,GetLastError());
        return;
    }

    ok( HFILE_ERROR != _lwrite( filehandle, "", 0 ), "_hwrite complains\n" );

    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    filehandle = _lopen( filename, OF_READ );

    bytes_read = _hread( filehandle, buffer, 1);

    ok( 0 == bytes_read, "file read size error\n" );

    ok( HFILE_ERROR != _lclose(filehandle), "_lclose complains\n" );

    filehandle = _lopen( filename, OF_READWRITE );

    bytes_written = 0;
    checksum[0] = '\0';
    srand( (unsigned)time( NULL ) );
    for (blocks = 0; blocks < 100; blocks++)
    {
        for (i = 0; i < (INT)sizeof( buffer ); i++)
        {
            buffer[i] = rand(  );
            checksum[0] = checksum[0] + buffer[i];
        }
        ok( HFILE_ERROR != _lwrite( filehandle, buffer, sizeof( buffer ) ), "_hwrite complains\n" );
        bytes_written = bytes_written + sizeof( buffer );
    }

    ok( HFILE_ERROR != _lwrite( filehandle, checksum, 1 ), "_hwrite complains\n" );
    bytes_written++;

    ok( HFILE_ERROR != _lclose( filehandle ), "_lclose complains\n" );

    memory_object = LocalAlloc( LPTR, bytes_written );

    ok( 0 != memory_object, "LocalAlloc fails, could be out of memory\n" );

    contents = LocalLock( memory_object );
    ok( NULL != contents, "LocalLock whines\n" );

    filehandle = _lopen( filename, OF_READ );

    contents = LocalLock( memory_object );
    ok( NULL != contents, "LocalLock whines\n" );

    ok( bytes_written == _hread( filehandle, contents, bytes_written), "read length differ from write length\n" );

    checksum[0] = '\0';
    i = 0;
    do
    {
        checksum[0] += contents[i];
        i++;
    }
    while (i < bytes_written - 1);

    ok( checksum[0] == contents[i], "stored checksum differ from computed checksum\n" );

    ok( HFILE_ERROR != _lclose( filehandle ), "_lclose complains\n" );

    ret = DeleteFileA( filename );
    ok( ret, "DeleteFile failed (%d)\n", GetLastError(  ) );

    LocalFree( contents );
}