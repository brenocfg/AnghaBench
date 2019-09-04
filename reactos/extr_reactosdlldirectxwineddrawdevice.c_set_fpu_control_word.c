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
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */

__attribute__((used)) static inline void set_fpu_control_word(WORD fpucw)
{
#if defined(__i386__) && defined(__GNUC__)
    __asm__ volatile ("fldcw %0" : : "m" (fpucw));
#elif defined(__i386__) && defined(_MSC_VER)
    __asm fldcw fpucw;
#endif
}