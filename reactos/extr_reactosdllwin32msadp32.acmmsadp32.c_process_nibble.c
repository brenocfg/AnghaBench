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
struct TYPE_3__ {int iCoef1; int iCoef2; } ;
typedef  TYPE_1__ ADPCMCOEFSET ;

/* Variables and functions */
 int* MS_Delta ; 
 int /*<<< orphan*/  clamp_sample (int*) ; 

__attribute__((used)) static inline void process_nibble(unsigned nibble, int* idelta,
                                  int* sample1, int* sample2,
                                  const ADPCMCOEFSET* coeff)
{
    int sample;
    int snibble;

    /* nibble is in fact a signed 4 bit integer => propagate sign if needed */
    snibble = (nibble & 0x08) ? (nibble - 16) : nibble;
    sample = ((*sample1 * coeff->iCoef1) + (*sample2 * coeff->iCoef2)) / 256 +
        snibble * *idelta;
    clamp_sample(&sample);

    *sample2 = *sample1;
    *sample1 = sample;
    *idelta = ((MS_Delta[nibble] * *idelta) / 256);
    if (*idelta < 16) *idelta = 16;
}