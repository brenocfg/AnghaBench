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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  _NKEYBRD_READ ; 
 int _bios_keybrd (int /*<<< orphan*/ ) ; 
 scalar_t__ _getch () ; 
 scalar_t__ errno ; 
 int pc_keymap (int) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
gl_getc(void)
/* get a character without echoing it to screen */
{
    int             c;
#ifdef __unix__
    char            ch;
#endif

#ifdef __unix__
    ch = '\0';
    while ((c = (int) read(0, &ch, 1)) == -1) {
	if (errno != EINTR)
	    break;
    }
    if (c != (-1))
	    c = (int) ch;
#endif	/* __unix__ */
#ifdef MSDOS
    c = _bios_keybrd(_NKEYBRD_READ);
    if ((c & 0377) == 224) {
	c = pc_keymap((c >> 8) & 0377);
    } else {
	c &= 0377;
    }
#endif /* MSDOS */
#ifdef __windows__
	c = (int) _getch();
	if ((c == 0) || (c == 0xE0)) {
		/* Read key code */
		c = (int) _getch();
		c = pc_keymap(c);
	} else if (c == '\r') {
		/* Note: we only get \r from the console,
		 * and not a matching \n.
		 */
		c = '\n';
	}
#endif
    return c;
}