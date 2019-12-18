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
 int /*<<< orphan*/  ITALIC ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  SetCl (int /*<<< orphan*/ ) ; 
 scalar_t__ putchar (char) ; 

void th_outp(char *cur_string, char *THtag)
{
    int symbol;
    putchar('\n');
    putchar('\n');
    putchar('\t');
    putchar('\t');
    SetCl(ITALIC);
     for(symbol=3;putchar(THtag[symbol]); symbol++);
    putchar('\n');
    SetCl(NORMAL);
}