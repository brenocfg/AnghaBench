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
 char DIR_SEPARATOR_CHAR ; 
 char toupper (char) ; 

void normalize_dirname(char *filename)
{
    int i, tgt;
    int slash = 1;

    for (i = 0, tgt = 0; filename[i]; i++)
    {
        if (slash)
        {
            if (filename[i] != '/' && filename[i] != '\\')
            {
                filename[tgt++] = toupper(filename[i]);
                slash = 0;
            }
        }
        else
        {
            if (filename[i] == '/' || filename[i] == '\\')
            {
                slash = 1;
                filename[tgt++] = DIR_SEPARATOR_CHAR;
            }
            else
            {
                filename[tgt++] = toupper(filename[i]);
            }
        }
    }
    filename[tgt] = '\0'; // NULL-terminate
}