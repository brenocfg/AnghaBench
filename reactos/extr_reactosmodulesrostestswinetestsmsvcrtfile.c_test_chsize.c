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
typedef  int /*<<< orphan*/  temptext ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int _O_CREAT ; 
 int _O_RDWR ; 
 int _O_TRUNC ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 scalar_t__ _chsize (int,int) ; 
 int /*<<< orphan*/  _close (int) ; 
 int _filelength (int) ; 
 scalar_t__ _lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _open (char*,int,int) ; 
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  _unlink (char*) ; 
 scalar_t__ _write (int,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_chsize( void )
{
    int fd;
    LONG cur, pos, count;
    char temptext[] = "012345678";
    char *tempfile = _tempnam( ".", "tst" );
    
    ok( tempfile != NULL, "Couldn't create test file: %s\n", tempfile );

    fd = _open( tempfile, _O_CREAT|_O_TRUNC|_O_RDWR, _S_IREAD|_S_IWRITE );
    ok( fd > 0, "Couldn't open test file\n" );

    count = _write( fd, temptext, sizeof(temptext) );
    ok( count > 0, "Couldn't write to test file\n" );

    /* get current file pointer */
    cur = _lseek( fd, 0, SEEK_CUR );

    /* make the file smaller */
    ok( _chsize( fd, sizeof(temptext) / 2 ) == 0, "_chsize() failed\n" );

    pos = _lseek( fd, 0, SEEK_CUR );
    ok( cur == pos, "File pointer changed from: %d to: %d\n", cur, pos );
    ok( _filelength( fd ) == sizeof(temptext) / 2, "Wrong file size\n" );

    /* enlarge the file */
    ok( _chsize( fd, sizeof(temptext) * 2 ) == 0, "_chsize() failed\n" ); 

    pos = _lseek( fd, 0, SEEK_CUR );
    ok( cur == pos, "File pointer changed from: %d to: %d\n", cur, pos );
    ok( _filelength( fd ) == sizeof(temptext) * 2, "Wrong file size\n" );

    _close( fd );
    _unlink( tempfile );
    free( tempfile );
}