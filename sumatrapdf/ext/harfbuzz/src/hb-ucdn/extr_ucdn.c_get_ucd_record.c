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
typedef  int /*<<< orphan*/  UCDRecord ;

/* Variables and functions */
 int SHIFT1 ; 
 int SHIFT2 ; 
 int* index0 ; 
 int* index1 ; 
 int* index2 ; 
 int /*<<< orphan*/  const* ucd_records ; 

__attribute__((used)) static const UCDRecord *get_ucd_record(uint32_t code)
{
    int index, offset;

    if (code >= 0x110000)
        index = 0;
    else {
        index  = index0[code >> (SHIFT1+SHIFT2)] << SHIFT1;
        offset = (code >> SHIFT2) & ((1<<SHIFT1) - 1);
        index  = index1[index + offset] << SHIFT2;
        offset = code & ((1<<SHIFT2) - 1);
        index  = index2[index + offset];
    }

    return &ucd_records[index];
}