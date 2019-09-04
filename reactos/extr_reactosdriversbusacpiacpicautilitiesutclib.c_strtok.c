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
 char* strpbrk (char*,char const*) ; 

char*
strtok (
    char                    *String,
    const char              *Delimiters)
{
    char                    *Begin = String;
    static char             *SavedPtr;


    if (Begin == NULL)
    {
        if (SavedPtr == NULL)
        {
            return (NULL);
        }
        Begin = SavedPtr;
    }

    SavedPtr = strpbrk (Begin, Delimiters);
    while (SavedPtr == Begin)
    {
        *Begin++ = '\0';
        SavedPtr = strpbrk (Begin, Delimiters);
    }

    if (SavedPtr)
    {
        *SavedPtr++ = '\0';
        return (Begin);
    }
    else
    {
        return (NULL);
    }
}