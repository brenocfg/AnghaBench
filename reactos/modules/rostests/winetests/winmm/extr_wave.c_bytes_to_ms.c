#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nSamplesPerSec; } ;
typedef  TYPE_1__* LPWAVEFORMATEX ;
typedef  int DWORD ;

/* Variables and functions */
 int bytes_to_samples (int,TYPE_1__*) ; 

DWORD bytes_to_ms(DWORD bytes, LPWAVEFORMATEX pwfx)
{
    return bytes_to_samples(bytes, pwfx) * 1000 / pwfx->nSamplesPerSec;
}