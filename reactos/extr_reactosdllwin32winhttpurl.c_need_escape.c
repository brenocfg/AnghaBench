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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isalnumW (int) ; 

__attribute__((used)) static BOOL need_escape( WCHAR c )
{
    if (isalnumW( c )) return FALSE;

    if (c <= 31 || c >= 127) return TRUE;
    else
    {
        switch (c)
        {
        case ' ':
        case '"':
        case '#':
        case '%':
        case '<':
        case '>':
        case ']':
        case '\\':
        case '[':
        case '^':
        case '`':
        case '{':
        case '|':
        case '}':
        case '~':
            return TRUE;
        default:
            return FALSE;
        }
    }
}