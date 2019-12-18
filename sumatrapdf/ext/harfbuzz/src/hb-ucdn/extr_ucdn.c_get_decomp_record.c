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
typedef  int uint32_t ;

/* Variables and functions */
 int DECOMP_SHIFT1 ; 
 int DECOMP_SHIFT2 ; 
 unsigned short const* decomp_data ; 
 int* decomp_index0 ; 
 int* decomp_index1 ; 
 int* decomp_index2 ; 

__attribute__((used)) static const unsigned short *get_decomp_record(uint32_t code)
{
    int index, offset;

    if (code >= 0x110000)
        index = 0;
    else {
        index  = decomp_index0[code >> (DECOMP_SHIFT1+DECOMP_SHIFT2)]
            << DECOMP_SHIFT1;
        offset = (code >> DECOMP_SHIFT2) & ((1<<DECOMP_SHIFT1) - 1);
        index  = decomp_index1[index + offset] << DECOMP_SHIFT2;
        offset = code & ((1<<DECOMP_SHIFT2) - 1);
        index  = decomp_index2[index + offset];
    }

    return &decomp_data[index];
}