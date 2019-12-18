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
 int /*<<< orphan*/  ULONG_ONEZERO ; 
 unsigned long ULONG_ZEROONE ; 
 scalar_t__ memtest_addressing (unsigned long*,size_t,int) ; 
 scalar_t__ memtest_compare_times (unsigned long*,size_t,int,int,int) ; 
 int /*<<< orphan*/  memtest_fill_random (unsigned long*,size_t,int) ; 
 int /*<<< orphan*/  memtest_fill_value (unsigned long*,size_t,int /*<<< orphan*/ ,unsigned long,char,int) ; 
 int /*<<< orphan*/  memtest_progress_end () ; 
 int /*<<< orphan*/  memtest_progress_start (char*,int) ; 

int memtest_test(unsigned long *m, size_t bytes, int passes, int interactive) {
    int pass = 0;
    int errors = 0;

    while (pass != passes) {
        pass++;

        if (interactive) memtest_progress_start("Addressing test",pass);
        errors += memtest_addressing(m,bytes,interactive);
        if (interactive) memtest_progress_end();

        if (interactive) memtest_progress_start("Random fill",pass);
        memtest_fill_random(m,bytes,interactive);
        if (interactive) memtest_progress_end();
        errors += memtest_compare_times(m,bytes,pass,4,interactive);

        if (interactive) memtest_progress_start("Solid fill",pass);
        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S',interactive);
        if (interactive) memtest_progress_end();
        errors += memtest_compare_times(m,bytes,pass,4,interactive);

        if (interactive) memtest_progress_start("Checkerboard fill",pass);
        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C',interactive);
        if (interactive) memtest_progress_end();
        errors += memtest_compare_times(m,bytes,pass,4,interactive);
    }
    return errors;
}