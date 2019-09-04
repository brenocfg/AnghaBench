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
 int _getch () ; 
 int _putch (int) ; 
 scalar_t__ char_avail ; 

int _getche(void)
{
  if (char_avail)
    /*
     * We don't know, wether the ungot char was already echoed
     * we assume yes (for example in cscanf, probably the only
     * place where ungetch is ever called.
     * There is no way to check for this really, because
     * ungetch could have been called with a character that
     * hasn't been got by a conio function.
     * We don't echo again.
     */
    return(_getch());
  return (_putch(_getch()));
}