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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int open (char const*,int) ; 
 int pread (int,int*,int,int) ; 
 int pwrite (int,int*,int,int) ; 
 int /*<<< orphan*/  safe_close (int) ; 

__attribute__((used)) static void bit_toggle(const char *fn, uint64_t p) {
        uint8_t b;
        ssize_t r;
        int fd;

        fd = open(fn, O_RDWR|O_CLOEXEC);
        assert_se(fd >= 0);

        r = pread(fd, &b, 1, p/8);
        assert_se(r == 1);

        b ^= 1 << (p % 8);

        r = pwrite(fd, &b, 1, p/8);
        assert_se(r == 1);

        safe_close(fd);
}