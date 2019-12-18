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
typedef  int /*<<< orphan*/  dsize ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FlushConsoleInputBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  ZeroMemory (char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cputs (char const* const) ; 
 scalar_t__ _getch () ; 
 int /*<<< orphan*/  _putch (char) ; 
 int /*<<< orphan*/  gl_cleanup () ; 
 int gl_getc () ; 
 int /*<<< orphan*/  gl_init () ; 
 int /*<<< orphan*/  gl_putc (char) ; 
 int /*<<< orphan*/  gl_puts (char const* const) ; 
 int /*<<< orphan*/  memset (char* const,int /*<<< orphan*/ ,size_t) ; 

char *gl_getpass(const char *const prompt, char *const pass, int dsize)
{
#ifdef __unix__
	char *cp;
	int c;

	memset(pass, 0, (size_t) sizeof(dsize));
	dsize--;
	gl_init();

	/* Display the prompt first. */
	if ((prompt != NULL) && (prompt[0] != '\0'))
		gl_puts(prompt);

	cp = pass;
	while ((c = gl_getc()) != (-1)) {
		if ((c == '\r') || (c == '\n'))
			break;
		if ((c == '\010') || (c == '\177'))	{
			/* ^H and DEL */
			if (cp > pass) {
				*--cp = '\0';
				gl_putc('\010');
				gl_putc(' ');
				gl_putc('\010');
			}
		} else if (cp < (pass + dsize)) {
			gl_putc('*');
			*cp++ = c;
		}
	}
	*cp = '\0';
	gl_putc('\n');
	gl_cleanup();
	return (pass);
#else
#ifdef __windows__
	char *cp;
	int c;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	ZeroMemory(pass, (DWORD) sizeof(dsize));
	dsize--;

	if ((prompt != NULL) && (prompt[0] != '\0'))
		_cputs(prompt);

	for (cp = pass;;) {
		c = (int) _getch();
		if ((c == '\r') || (c == '\n'))
			break;
		if ((c == '\010') || (c == '\177'))	{
			/* ^H and DEL */
			if (cp > pass) {
				*--cp = '\0';
				_putch('\010');
				_putch(' ');
				_putch('\010');
			}
		} else if (cp < (pass + dsize)) {
			_putch('*');
			*cp++ = c;
		}
	}
	_putch('\r');
	_putch('\n');
	Sleep(40);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	*cp = '\0';
	return (pass);
#endif	/* __windows__ */
#endif	/* ! __unix__ */
}