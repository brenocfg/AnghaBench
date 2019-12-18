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
struct iovec {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 scalar_t__ _unlikely_ (int) ; 

__attribute__((used)) static inline size_t IOVEC_INCREMENT(struct iovec *i, size_t n, size_t k) {
        size_t j;

        for (j = 0; j < n; j++) {
                size_t sub;

                if (_unlikely_(k <= 0))
                        break;

                sub = MIN(i[j].iov_len, k);
                i[j].iov_len -= sub;
                i[j].iov_base = (uint8_t*) i[j].iov_base + sub;
                k -= sub;
        }

        return k;
}