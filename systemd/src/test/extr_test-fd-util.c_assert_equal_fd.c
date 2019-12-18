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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void assert_equal_fd(int fd1, int fd2) {

        for (;;) {
                uint8_t a[4096], b[4096];
                ssize_t x, y;

                x = read(fd1, a, sizeof(a));
                assert(x >= 0);

                y = read(fd2, b, sizeof(b));
                assert(y >= 0);

                assert(x == y);

                if (x == 0)
                        break;

                assert(memcmp(a, b, x) == 0);
        }
}