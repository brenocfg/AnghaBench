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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 unsigned char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static size_t dumpStr(FILE* inFile, FILE* outCFile)
{
    size_t bufLen = 0;
    unsigned char ch;

    /* Always start the first line */
    fprintf(outCFile, "\n    \"");
    do
    {
        /* Read the next byte */
        ch = fgetc(inFile);

        /* If a byte is available... */
        if (!feof(inFile))
        {
            /* ... do we need to start a new line? */
            if ((bufLen != 0) && (bufLen % 16) == 0)
            {
                /* Yes, end the current line and start a new one */
                fprintf(outCFile, "\"");
                fprintf(outCFile, "\n    \"");
            }

            /* Now write the byte */
            fprintf(outCFile, "\\x%02x", (unsigned int)ch);
        }
        /* ... otherwise, end the current line... */
        else
        {
            fprintf(outCFile, "\"");
            /* We break just after */
        }

        ++bufLen; // This takes also the final NULL terminator into account.

    } while (!feof(inFile));

    return bufLen;
}