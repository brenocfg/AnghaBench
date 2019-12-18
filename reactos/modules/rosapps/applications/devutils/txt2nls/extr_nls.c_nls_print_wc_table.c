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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
nls_print_wc_table(uint16_t *wc_table, uint16_t default_char, int is_dbcs)
{
    uint32_t ch;

    printf("WCTABLE:\n");

    for (ch = 0; ch <= 0xFFFF; ch++)
    {
        /* DBCS code page */
        if (is_dbcs)
        {
            uint16_t *table = (uint16_t*)wc_table;

            if (table[ch] != default_char)
                printf("0x%04X 0x%04X\n", (unsigned int)ch, (unsigned int)table[ch]);
        }
        /* SBCS code page */
        else
        {
            uint8_t *table = (uint8_t*)wc_table;

            if (table[ch] != default_char)
                printf("0x%04X 0x%02X\n", (unsigned int)ch, (unsigned int)table[ch]);
        }
    }

    printf("\n");
}