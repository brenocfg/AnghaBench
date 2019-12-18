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

char*
GetNextLine(char *pszLine)
{
    /* Walk to the end of the line */
    while (*pszLine != 13 && *pszLine != 10 && *pszLine != 0) pszLine++;

    /* Skip one CR/LF */
    if (pszLine[0] == 13 && pszLine[1] == 10)
        pszLine += 2;
    else if (pszLine[0] == 13 || pszLine[0] == 10)
        pszLine++;

    if (*pszLine == 0)
    {
        return 0;
    }

    return pszLine;
}