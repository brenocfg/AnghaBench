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
typedef  char uint8_t ;

/* Variables and functions */
 scalar_t__ isprint (char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
display_mbr(const uint8_t *mbr, size_t len)
{
    unsigned char c = 0;
    unsigned int i = 0, j = 0;

    printf("sizeof(MBR): %zu bytes\n", len);
    for (i = 0; i < len; i++)
    {
        if (!(i % 16))
            printf("%04d ", i);

        if (!(i % 8))
            printf(" ");

        c = mbr[i];
        printf("%02x ", c);

        if (!((i + 1) % 16))
        {
            printf(" |");
            for (; j <= i; j++)
                printf("%c", isprint(mbr[j]) ? mbr[j] : '.');
            printf("|\n");
        }
    }
}