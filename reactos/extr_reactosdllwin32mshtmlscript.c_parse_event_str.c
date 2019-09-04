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
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ isalnumW (char) ; 
 scalar_t__ isspaceW (char) ; 

__attribute__((used)) static BOOL parse_event_str(WCHAR *event, const WCHAR **args)
{
    WCHAR *ptr;

    TRACE("%s\n", debugstr_w(event));

    for(ptr = event; isalnumW(*ptr); ptr++);
    if(!*ptr) {
        *args = NULL;
        return TRUE;
    }

    if(*ptr != '(')
        return FALSE;

    *ptr++ = 0;
    *args = ptr;
    while(isalnumW(*ptr) || isspaceW(*ptr) || *ptr == ',')
        ptr++;

    if(*ptr != ')')
        return FALSE;

    *ptr++ = 0;
    return !*ptr;
}