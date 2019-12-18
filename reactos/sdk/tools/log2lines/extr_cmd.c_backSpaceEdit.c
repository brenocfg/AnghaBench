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
#define  KDBG_BS_CHAR 128 

__attribute__((used)) static char
*backSpaceEdit(char *s)
{
    char c;
    char *edit = s;
    char *text = s;

    while (( c = *edit++ ))
    {
        switch (c)
        {
        case KDBG_BS_CHAR:
            if (text > s)
                text --;
            break;
        default:
            *text++ = c;
        }
    }
    *text = '\0';

    return s;
}