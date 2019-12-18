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
typedef  scalar_t__ REGEDIT_ACTION ;
typedef  char* LPSTR ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ACTION_ADD ; 
 scalar_t__ ACTION_DELETE ; 
 scalar_t__ ACTION_EXPORT ; 
 scalar_t__ ACTION_UNDEF ; 
 scalar_t__ ACTION_VIEW ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PerformRegAction (scalar_t__,char*) ; 
 int /*<<< orphan*/  error_unknown_switch (char,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char toupper (char) ; 
 char* usage ; 

BOOL ProcessCmdLine(LPSTR lpCmdLine)
{
    REGEDIT_ACTION action = ACTION_UNDEF;
    LPSTR s = lpCmdLine;        /* command line pointer */
    CHAR ch = *s;               /* current character */

    while (ch && ((ch == '-') || (ch == '/'))) {
        char chu;
        char ch2;

        s++;
        ch = *s;
        ch2 = *(s+1);
        chu = toupper(ch);
        if (!ch2 || isspace(ch2)) {
            if (chu == 'S' || chu == 'V') {
                /* ignore these switches */
            } else {
                switch (chu) {
                case 'D':
                    action = ACTION_DELETE;
                    break;
                case 'E':
                    action = ACTION_EXPORT;
                    break;
                case 'V':
                    action = ACTION_VIEW;
                    break;
                case '?':
                    printf(usage);
                    return FALSE;
                    //exit(0);
                    break;
                default:
                    error_unknown_switch(chu, s);
                    return FALSE;
                    break;
                }
            }
            s++;
        } else {
            if (ch2 == ':') {
                switch (chu) {
                case 'L':
                    /* fall through */
                case 'R':
                    s += 2;
                    while (*s && !isspace(*s)) {
                        s++;
                    }
                    break;
                default:
                    error_unknown_switch(chu, s);
                    return FALSE;
                    break;
                }
            } else {
                /* this is a file name, starting from '/' */
                s--;
                break;
            }
        }
        /* skip spaces to the next parameter */
        ch = *s;
        while (ch && isspace(ch)) {
            s++;
            ch = *s;
        }
    }
    if (action == ACTION_UNDEF) {
        action = ACTION_ADD;
    }
    return PerformRegAction(action, s);
}