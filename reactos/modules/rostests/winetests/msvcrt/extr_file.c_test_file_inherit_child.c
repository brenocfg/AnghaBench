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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void test_file_inherit_child(const char* fd_s)
{
    int fd = atoi(fd_s);
    char buffer[32];
    int ret;

    ret =write(fd, "Success", 8);
    ok( ret == 8, "Couldn't write in child process on %d (%s)\n", fd, strerror(errno));
    lseek(fd, 0, SEEK_SET);
    ok(read(fd, buffer, sizeof (buffer)) == 8, "Couldn't read back the data\n");
    ok(memcmp(buffer, "Success", 8) == 0, "Couldn't read back the data\n");
}