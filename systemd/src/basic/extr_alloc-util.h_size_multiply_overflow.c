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
 size_t SIZE_MAX ; 
 int _unlikely_ (int) ; 

__attribute__((used)) static inline bool size_multiply_overflow(size_t size, size_t need) {
        return _unlikely_(need != 0 && size > (SIZE_MAX / need));
}