#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {int CodePage; int MaximumCharacterSize; int DefaultChar; int UniDefaultChar; int TransUniDefaultChar; int* LeadByte; } ;
typedef  TYPE_1__ NLS_FILE_HEADER ;

/* Variables and functions */
 size_t MAXIMUM_LEADBYTES ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
nls_print_header(NLS_FILE_HEADER *header)
{
    uint32_t i;

    printf("HEADER:\n");
    printf("CodePage: %u\n", header->CodePage);
    printf("Character size: %u\n", header->MaximumCharacterSize);
    printf("Default char: 0x%02X\n", header->DefaultChar);
    printf("Default unicode char: 0x%04X\n", header->UniDefaultChar);
    printf("Trans default char: 0x%02X\n", header->TransUniDefaultChar);
    printf("Trans default unicode char: 0x%04X\n", header->TransUniDefaultChar);

    for (i = 0; i < MAXIMUM_LEADBYTES; i++)
    {
        printf("LeadByte[%u] = 0x%02X\n", i, header->LeadByte[i]);
    }

    printf("\n");
}