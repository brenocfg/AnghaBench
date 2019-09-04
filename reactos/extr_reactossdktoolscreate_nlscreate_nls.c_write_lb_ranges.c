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
typedef  int /*<<< orphan*/  sub_table ;
typedef  int /*<<< orphan*/  offsets ;
typedef  scalar_t__ WORD ;
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int* LeadByte; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CPINFOEXA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAKEWORD (int,int) ; 
 int MAX_LEADBYTES ; 
 int /*<<< orphan*/  TRUE ; 
 int fwrite (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL write_lb_ranges(FILE *out, CPINFOEXA *cpi, WCHAR *table)
{
    WCHAR sub_table[256];
    WORD offset, offsets[256];
    int i, j, range;

    memset(offsets, 0, sizeof(offsets));

    offset = 0;

    for(i = 0; i < MAX_LEADBYTES; i += 2) {
        for(range = cpi->LeadByte[i]; range != 0 && range <= cpi->LeadByte[i + 1]; range++) {
            offset += 256;
            offsets[range] = offset;
        }
    }

    if(fwrite(offsets, 1, sizeof(offsets), out) != sizeof(offsets))
        return FALSE;

    for(i = 0; i < MAX_LEADBYTES; i += 2) {
        for(range = cpi->LeadByte[i]; range != 0 && range <= cpi->LeadByte[i + 1]; range++) {
            /*printf("Writing sub table for LeadByte %02X\n", range);*/
            for(j = MAKEWORD(0, range); j <= MAKEWORD(0xFF, range); j++) {
                sub_table[j - MAKEWORD(0, range)] = table[j];
            }

            if(fwrite(sub_table, 1, sizeof(sub_table), out) != sizeof(sub_table))
                return FALSE;
        }
    }

    return TRUE;
}