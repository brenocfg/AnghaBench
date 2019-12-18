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
 int LBASE ; 
 int NCOUNT ; 
 int SBASE ; 
 int SCOUNT ; 
 int TBASE ; 
 int TCOUNT ; 
 int VBASE ; 

__attribute__((used)) static int hangul_pair_decompose(uint32_t code, uint32_t *a, uint32_t *b)
{
    int si = code - SBASE;

    if (si < 0 || si >= SCOUNT)
        return 0;

    if (si % TCOUNT) {
        /* LV,T */
        *a = SBASE + (si / TCOUNT) * TCOUNT;
        *b = TBASE + (si % TCOUNT);
        return 3;
    } else {
        /* L,V */
        *a = LBASE + (si / NCOUNT);
        *b = VBASE + (si % NCOUNT) / TCOUNT;
        return 2;
    }
}