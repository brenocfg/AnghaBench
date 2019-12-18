#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ handle; int wxflag; } ;
typedef  TYPE_1__ ioinfo ;
struct TYPE_9__ {int _file; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int EBADF ; 
 int EOF ; 
 size_t MSVCRT_FD_BLOCK_SIZE ; 
 size_t STDIN_FILENO ; 
 TYPE_1__** __pioinfo ; 
 int _flsbuf (char,TYPE_2__*) ; 
 scalar_t__ _get_osfhandle (size_t) ; 
 int close (size_t) ; 
 int errno ; 
 int fclose (TYPE_2__*) ; 
 int fread (char*,int,int,TYPE_2__*) ; 
 int fwrite (char*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int read (size_t,char*,int) ; 
 TYPE_2__* stdin ; 
 int write (size_t,char*,int) ; 

__attribute__((used)) static void test_invalid_stdin_child( void )
{
    HANDLE handle;
    ioinfo *info;
    int ret;
    char c;

    errno = 0xdeadbeef;
    handle = (HANDLE)_get_osfhandle(STDIN_FILENO);
    ok(handle == (HANDLE)-2, "handle = %p\n", handle);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    info = &__pioinfo[STDIN_FILENO/MSVCRT_FD_BLOCK_SIZE][STDIN_FILENO%MSVCRT_FD_BLOCK_SIZE];
    ok(info->handle == (HANDLE)-2, "info->handle = %p\n", info->handle);
    ok(info->wxflag == 0xc1, "info->wxflag = %x\n", info->wxflag);

    ok(stdin->_file == -2, "stdin->_file = %d\n", stdin->_file);

    errno = 0xdeadbeef;
    ret = fread(&c, 1, 1, stdin);
    ok(!ret, "fread(stdin) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = read(-2, &c, 1);
    ok(ret == -1, "read(-2) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = read(STDIN_FILENO, &c, 1);
    ok(ret == -1, "read(STDIN_FILENO) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = _flsbuf('a', stdin);
    ok(ret == EOF, "_flsbuf(stdin) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = fwrite(&c, 1, 1, stdin);
    ok(!ret, "fwrite(stdin) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = write(-2, &c, 1);
    ok(ret == -1, "write(-2) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = write(STDIN_FILENO, &c, 1);
    ok(ret == -1, "write(STDIN_FILENO) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = fclose(stdin);
    ok(ret == -1, "fclose(stdin) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = close(-2);
    ok(ret == -1, "close(-2) returned %d\n", ret);
    ok(errno == EBADF, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = close(STDIN_FILENO);
    ok(ret==-1 || !ret, "close(STDIN_FILENO) returned %d\n", ret);
    ok((ret==-1 && errno==EBADF) || (!ret && errno==0xdeadbeef), "errno = %d\n", errno);
}