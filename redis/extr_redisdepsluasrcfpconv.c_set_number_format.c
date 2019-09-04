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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void set_number_format(char *fmt, int precision)
{
    int d1, d2, i;

    assert(1 <= precision && precision <= 14);

    /* Create printf format (%.14g) from precision */
    d1 = precision / 10;
    d2 = precision % 10;
    fmt[0] = '%';
    fmt[1] = '.';
    i = 2;
    if (d1) {
        fmt[i++] = '0' + d1;
    }
    fmt[i++] = '0' + d2;
    fmt[i++] = 'g';
    fmt[i] = 0;
}