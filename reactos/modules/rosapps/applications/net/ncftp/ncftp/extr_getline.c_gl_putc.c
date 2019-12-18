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
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void
gl_putc(int c)
{
    char   ch = (char) (unsigned char) c;

    write(1, &ch, 1);
    if (ch == '\n') {
	ch = '\r';
        write(1, &ch, 1);	/* RAW mode needs '\r', does not hurt */
    }
}