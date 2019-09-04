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
 int /*<<< orphan*/  _putch (char) ; 

__attribute__((used)) static int test_console_putch(void)
{
    int result = 0;

    _putch('1');
    _putch('@');
    _putch('3');
    _putch(':');
    _putch('\n');
    _putch('a');
    _putch('B');
    _putch('c');
    _putch(':');
    _putch('\n');
    return result;
}