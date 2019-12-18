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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static unsigned short readushort(FILE * f, int bigendian)
{
    unsigned char c1, c2;
    if (!fread(&c1, 1, 1, f)) {
        fprintf(stderr,
                "\nError: fread return a number of element different from the expected.\n");
        return 0;
    }
    if (!fread(&c2, 1, 1, f)) {
        fprintf(stderr,
                "\nError: fread return a number of element different from the expected.\n");
        return 0;
    }
    if (bigendian) {
        return (unsigned short)((c1 << 8) + c2);
    } else {
        return (unsigned short)((c2 << 8) + c1);
    }
}