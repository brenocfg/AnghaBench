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
typedef  int /*<<< orphan*/  DestBpp ;

/* Variables and functions */
 int /*<<< orphan*/  Generate (char*,unsigned int) ; 

int
main(int argc, char *argv[])
{
    unsigned Index;
    static unsigned DestBpp[] =
    { 8, 16, 32 };

    if (argc < 2)
        return 0;

    for (Index = 0; Index < sizeof(DestBpp) / sizeof(DestBpp[0]); Index++)
    {
        Generate(argv[1], DestBpp[Index]);
    }

    return 0;
}