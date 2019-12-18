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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _O_CREAT ; 
 int /*<<< orphan*/  _O_RDONLY ; 
 int _O_RDWR ; 
 int /*<<< orphan*/  _SH_DENYRW ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  _close (int) ; 
 scalar_t__ _get_osfhandle (int) ; 
 int _open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _sopen (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _unlink (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_get_osfhandle(void)
{
    int fd;
    char fname[] = "t_get_osfhanle";
    DWORD bytes_written;
    HANDLE handle;

    fd = _sopen(fname, _O_CREAT|_O_RDWR, _SH_DENYRW, _S_IREAD | _S_IWRITE);
    handle = (HANDLE)_get_osfhandle(fd);
    WriteFile(handle, "bar", 3, &bytes_written, NULL);
    _close(fd);
    fd = _open(fname, _O_RDONLY, 0);
    ok(fd != -1, "Couldn't open '%s' after _get_osfhandle()\n", fname);

    _close(fd);
    _unlink(fname);

    errno = 0xdeadbeef;
    handle = (HANDLE)_get_osfhandle(fd);
    ok(handle == INVALID_HANDLE_VALUE, "_get_osfhandle returned %p\n", handle);
    ok(errno == EBADF, "errno = %d\n", errno);
}