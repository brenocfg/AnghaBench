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
typedef  int DWORD ;

/* Variables and functions */
 int HEIGHT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void DumpCharacterFontData(DWORD BmpBits[])
{
    static int iBegin = 0;
    int i;

    fprintf(stdout, "    ");

    for (i = 0; i < HEIGHT; i++)
        fprintf(stdout, "0x%02lX, ", BmpBits[i]);

    fprintf(stdout, " // %d\n", iBegin);
    iBegin += HEIGHT;
}