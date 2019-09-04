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
struct stat {int st_mode; int st_dev; int st_rdev; int st_nlink; int st_size; } ;

/* Variables and functions */
 int ENOENT ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int _S_IFCHR ; 
 int _S_IFDIR ; 
 int _S_IFIFO ; 
 int _S_IFMT ; 
 int _S_IFREG ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 scalar_t__ _dup2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _pipe (int*,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ mkdir (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  skip (char*,int) ; 
 int stat (char*,struct stat*) ; 

__attribute__((used)) static void test_stat(void)
{
    int fd;
    int pipes[2];
    int ret;
    struct stat buf;

    /* Tests for a file */
    fd = open("stat.tst", O_WRONLY | O_CREAT | O_BINARY, _S_IREAD |_S_IWRITE);
    if (fd >= 0)
    {
        ret = fstat(fd, &buf);
        ok(!ret, "fstat failed: errno=%d\n", errno);
        ok((buf.st_mode & _S_IFMT) == _S_IFREG, "bad format = %06o\n", buf.st_mode);
        ok((buf.st_mode & 0777) == 0666, "bad st_mode = %06o\n", buf.st_mode);
        ok(buf.st_dev == 0, "st_dev is %d, expected 0\n", buf.st_dev);
        ok(buf.st_dev == buf.st_rdev, "st_dev (%d) and st_rdev (%d) differ\n", buf.st_dev, buf.st_rdev);
        ok(buf.st_nlink == 1, "st_nlink is %d, expected 1\n", buf.st_nlink);
        ok(buf.st_size == 0, "st_size is %d, expected 0\n", buf.st_size);

        ret = stat("stat.tst", &buf);
        ok(!ret, "stat failed: errno=%d\n", errno);
        ok((buf.st_mode & _S_IFMT) == _S_IFREG, "bad format = %06o\n", buf.st_mode);
        ok((buf.st_mode & 0777) == 0666, "bad st_mode = %06o\n", buf.st_mode);
        ok(buf.st_dev == buf.st_rdev, "st_dev (%d) and st_rdev (%d) differ\n", buf.st_dev, buf.st_rdev);
        ok(buf.st_nlink == 1, "st_nlink is %d, expected 1\n", buf.st_nlink);
        ok(buf.st_size == 0, "st_size is %d, expected 0\n", buf.st_size);

        errno = 0xdeadbeef;
        ret = stat("stat.tst\\", &buf);
        ok(ret == -1, "stat returned %d\n", ret);
        ok(errno == ENOENT, "errno = %d\n", errno);

        close(fd);
        remove("stat.tst");
    }
    else
        skip("open failed with errno %d\n", errno);

    /* Tests for a char device */
    if (_dup2(0, 10) == 0)
    {
        ret = fstat(10, &buf);
        ok(!ret, "fstat(stdin) failed: errno=%d\n", errno);
        if ((buf.st_mode & _S_IFMT) == _S_IFCHR)
        {
            ok(buf.st_mode == _S_IFCHR, "bad st_mode=%06o\n", buf.st_mode);
            ok(buf.st_dev == 10, "st_dev is %d, expected 10\n", buf.st_dev);
            ok(buf.st_rdev == 10, "st_rdev is %d, expected 10\n", buf.st_rdev);
            ok(buf.st_nlink == 1, "st_nlink is %d, expected 1\n", buf.st_nlink);
        }
        else
            skip("stdin is not a char device? st_mode=%06o\n", buf.st_mode);
        close(10);
    }
    else
        skip("_dup2 failed with errno %d\n", errno);

    /* Tests for pipes */
    if (_pipe(pipes, 1024, O_BINARY) == 0)
    {
        ret = fstat(pipes[0], &buf);
        ok(!ret, "fstat(pipe) failed: errno=%d\n", errno);
        ok(buf.st_mode == _S_IFIFO, "bad st_mode=%06o\n", buf.st_mode);
        ok(buf.st_dev == pipes[0], "st_dev is %d, expected %d\n", buf.st_dev, pipes[0]);
        ok(buf.st_rdev == pipes[0], "st_rdev is %d, expected %d\n", buf.st_rdev, pipes[0]);
        ok(buf.st_nlink == 1, "st_nlink is %d, expected 1\n", buf.st_nlink);
        close(pipes[0]);
        close(pipes[1]);
    }
    else
        skip("pipe failed with errno %d\n", errno);

    /* Tests for directory */
    if(mkdir("stat.tst") == 0)
    {
        ret = stat("stat.tst                         ", &buf);
        ok(!ret, "stat(directory) failed: errno=%d\n", errno);
        ok((buf.st_mode & _S_IFMT) == _S_IFDIR, "bad format = %06o\n", buf.st_mode);
        ok((buf.st_mode & 0777) == 0777, "bad st_mode = %06o\n", buf.st_mode);
        ok(buf.st_dev == buf.st_rdev, "st_dev (%d) and st_rdev (%d) differ\n", buf.st_dev, buf.st_rdev);
        ok(buf.st_nlink == 1, "st_nlink is %d, expected 1\n", buf.st_nlink);

        errno = 0xdeadbeef;
        ret = stat("stat.tst\\ ", &buf);
        ok(ret == -1, "stat returned %d\n", ret);
        ok(errno == ENOENT, "errno = %d\n", errno);
        rmdir( "stat.tst" );
    }
    else
        skip("mkdir failed with errno %d\n", errno);

    errno = 0xdeadbeef;
    ret = stat("c:", &buf);
    ok(ret == -1, "stat returned %d\n", ret);
    ok(errno == ENOENT, "errno = %d\n", errno);

    ret = stat("c:/", &buf);
    ok(!ret, "stat returned %d\n", ret);
    ok(buf.st_dev == 2, "st_dev = %d\n", buf.st_dev);
    ok(buf.st_rdev == 2, "st_rdev = %d\n", buf.st_rdev);
}