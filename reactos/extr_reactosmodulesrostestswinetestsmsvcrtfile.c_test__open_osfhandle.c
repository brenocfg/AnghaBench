#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int handle; int wxflag; } ;
typedef  TYPE_1__ ioinfo ;
typedef  int HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int) ; 
 int CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreatePipe (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int EBADF ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int INVALID_HANDLE_VALUE ; 
 int MSVCRT_FD_BLOCK_SIZE ; 
 TYPE_1__** __pioinfo ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test__open_osfhandle(void)
{
    ioinfo *info;
    HANDLE h, tmp;
    int fd;

    errno = 0xdeadbeef;
    fd = _open_osfhandle((intptr_t)INVALID_HANDLE_VALUE, 0);
    ok(fd == -1, "_open_osfhandle returned %d\n", fd);
    ok(errno == EBADF, "errno = %d\n", errno);

    h = CreateFileA("open_osfhandle.tst", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    fd = _open_osfhandle((intptr_t)h, 0);
    ok(fd > 0, "_open_osfhandle returned %d (%d)\n", fd, errno);
    info = &__pioinfo[fd/MSVCRT_FD_BLOCK_SIZE][fd%MSVCRT_FD_BLOCK_SIZE];
    ok(info->handle == h, "info->handle = %p, expected %p\n", info->handle, h);
    ok(info->wxflag == 1, "info->wxflag = %x, expected 1\n", info->wxflag);
    close(fd);
    ok(info->handle == INVALID_HANDLE_VALUE, "info->handle = %p, expected INVALID_HANDLE_VALUE\n", info->handle);
    ok(info->wxflag == 0, "info->wxflag = %x, expected 0\n", info->wxflag);
    DeleteFileA("open_osfhandle.tst");

    errno = 0xdeadbeef;
    fd = _open_osfhandle((intptr_t)h, 0);
    ok(fd == -1, "_open_osfhandle returned %d\n", fd);
    ok(errno == EBADF, "errno = %d\n", errno);

    ok(CreatePipe(&h, &tmp, NULL, 0), "CreatePipe failed\n");
    fd = _open_osfhandle((intptr_t)h, 0);
    ok(fd > 0, "_open_osfhandle returned %d (%d)\n", fd, errno);
    info = &__pioinfo[fd/MSVCRT_FD_BLOCK_SIZE][fd%MSVCRT_FD_BLOCK_SIZE];
    ok(info->handle == h, "info->handle = %p, expected %p\n", info->handle, h);
    ok(info->wxflag == 9, "info->wxflag = %x, expected 9\n", info->wxflag);
    close(fd);
    CloseHandle(tmp);
}