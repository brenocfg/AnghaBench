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
 int DISPLAY_COLUMNS ; 
 int LINE_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 size_t strlen (char const*) ; 

void OUTPUT_Line(const char *szLine)
{
    int spaceIndex = 0;
    char output[LINE_BUFFER_SIZE];

    memset(output, 0, DISPLAY_COLUMNS + 2);

    /*If this line is longer than DISPLAY_COLUMNS,
    * break it at the first space.
    */
    if (DISPLAY_COLUMNS - 2 < strlen(szLine))
    {
        for (spaceIndex = DISPLAY_COLUMNS / 2; spaceIndex < DISPLAY_COLUMNS - 2; spaceIndex++)
        {
            if (' ' == szLine[spaceIndex])
            {
                break;
            }
        }

        memcpy(output + 2, szLine, spaceIndex + 1);
        output[0] = '|';
        output[1] = ' ';
        output[strlen(output)] = '\n';
        printf(output);

        OUTPUT_Line(szLine + spaceIndex + 1);
    }
    else
    {
        sprintf(output,"| %s\n", szLine);
        printf(output);
    }

}