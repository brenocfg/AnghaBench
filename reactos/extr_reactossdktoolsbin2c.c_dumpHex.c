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
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 unsigned char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static size_t dumpHex(FILE* inFile, FILE* outCFile, char nullTerminate)
{
    size_t bufLen = 0;
    unsigned char ch;

    fprintf(outCFile, "\n{");
    do
    {
        /* Read the next byte */
        ch = fgetc(inFile);

        if (feof(inFile) && nullTerminate)
            ch = 0x00;

        if (!feof(inFile) || nullTerminate)
        {
            /* Start a new line if needed */
            if ((bufLen % 16) == 0)
                fprintf(outCFile, "\n   ");

            /* Write the byte or the optional NULL terminator */
            fprintf(outCFile, " 0x%02x,", (unsigned int)ch);

            ++bufLen;
        }
    } while (!feof(inFile));
    fprintf(outCFile, "\n}");

    return bufLen;
}