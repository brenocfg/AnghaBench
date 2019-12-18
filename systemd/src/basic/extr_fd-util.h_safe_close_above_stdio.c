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
 int safe_close (int) ; 

__attribute__((used)) static inline int safe_close_above_stdio(int fd) {
        if (fd < 3) /* Don't close stdin/stdout/stderr, but still invalidate the fd by returning -1 */
                return -1;

        return safe_close(fd);
}