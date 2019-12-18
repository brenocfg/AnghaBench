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
typedef  int /*<<< orphan*/  wbuffer ;
typedef  int /*<<< orphan*/  rbuffer ;

/* Variables and functions */
 int acquire_data_fd (char*,int,unsigned int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  random_bytes (char*,int) ; 
 int read (int,char*,int) ; 
 int safe_close (int) ; 
 int streq (char*,char*) ; 
 int /*<<< orphan*/  zero (char*) ; 

__attribute__((used)) static void test_acquire_data_fd_one(unsigned flags) {
        char wbuffer[196*1024 - 7];
        char rbuffer[sizeof(wbuffer)];
        int fd;

        fd = acquire_data_fd("foo", 3, flags);
        assert_se(fd >= 0);

        zero(rbuffer);
        assert_se(read(fd, rbuffer, sizeof(rbuffer)) == 3);
        assert_se(streq(rbuffer, "foo"));

        fd = safe_close(fd);

        fd = acquire_data_fd("", 0, flags);
        assert_se(fd >= 0);

        zero(rbuffer);
        assert_se(read(fd, rbuffer, sizeof(rbuffer)) == 0);
        assert_se(streq(rbuffer, ""));

        fd = safe_close(fd);

        random_bytes(wbuffer, sizeof(wbuffer));

        fd = acquire_data_fd(wbuffer, sizeof(wbuffer), flags);
        assert_se(fd >= 0);

        zero(rbuffer);
        assert_se(read(fd, rbuffer, sizeof(rbuffer)) == sizeof(rbuffer));
        assert_se(memcmp(rbuffer, wbuffer, sizeof(rbuffer)) == 0);

        fd = safe_close(fd);
}