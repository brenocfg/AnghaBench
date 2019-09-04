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

/* Variables and functions */
 scalar_t__ EBADF ; 
 int atoi (char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void test_file_inherit_child_no(const char* fd_s)
{
    int fd = atoi(fd_s);
    int ret;

    ret = write(fd, "Success", 8);
    ok( ret == -1 && errno == EBADF, 
       "Wrong write result in child process on %d (%s)\n", fd, strerror(errno));
}