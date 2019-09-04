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
typedef  int /*<<< orphan*/  ULONG ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gLineCount ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

BOOLEAN
NextLine(PCHAR LineBuffer,
         ULONG BufferSize,
         FILE *File)
{
    PCHAR p, pp;

    /* Scan each line */
    while (fgets(LineBuffer, BufferSize, File))
    {
        /* Remember it */
        gLineCount++;

        /* Reset the pointer at the beginning of the line */
        p = LineBuffer;

        /* Now bypass all whitespace (and tabspace) */
        while ((*p) && ((*p == ' ') || (*p == '\t'))) p++;

        /* If this is an old-style comment, skip the line */
        if (*p == ';')  continue;

        /* Otherwise, check for new-style comment */
        pp = strstr(p, "//");
        if (pp)
        {
            /* We have a comment, so terminate there (unless the whole line is one) */
            if (pp == p) continue;
            *pp = '\0';
        }
        else
        {
            /* No comment, so find the new line and terminate there */
            p = strchr(p, '\n');
            if (p) *p = '\0';
        }

        /* We have a line! */
        return TRUE;
    }

    /* No line found */
    return FALSE;
}