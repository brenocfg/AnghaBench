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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fread (unsigned long*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

unsigned long
findRev(FILE *finx, int *rev)
{
    unsigned long pos = 0L;

    while (!fseek(finx, (*rev) * sizeof(unsigned long), SEEK_SET))
    {
        fread(&pos, sizeof(long), 1, finx);
        (*rev)--;
        if (pos)
            break;
    }
    return pos;
}