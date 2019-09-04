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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tty_char_available () ; 

__attribute__((used)) static int
ttyread(void)
{
	char rb;

	if (tty_char_available()) {
		read(STDIN_FILENO, &rb, 1);
		return (rb & 0xff);
	} else {
		return (-1);
	}
}