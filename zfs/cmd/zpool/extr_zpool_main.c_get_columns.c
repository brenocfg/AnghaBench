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
struct winsize {int ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_columns(void)
{
	struct winsize ws;
	int columns = 80;
	int error;

	if (isatty(STDOUT_FILENO)) {
		error = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
		if (error == 0)
			columns = ws.ws_col;
	} else {
		columns = 999;
	}

	return (columns);
}