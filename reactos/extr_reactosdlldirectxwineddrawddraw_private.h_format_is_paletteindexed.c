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
struct TYPE_3__ {int dwFlags; } ;
typedef  int DWORD ;
typedef  TYPE_1__ DDPIXELFORMAT ;
typedef  int BOOL ;

/* Variables and functions */
 int DDPF_PALETTEINDEXED1 ; 
 int DDPF_PALETTEINDEXED2 ; 
 int DDPF_PALETTEINDEXED4 ; 
 int DDPF_PALETTEINDEXED8 ; 
 int DDPF_PALETTEINDEXEDTO8 ; 

__attribute__((used)) static inline BOOL format_is_paletteindexed(const DDPIXELFORMAT *fmt)
{
    DWORD flags = DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED4
            | DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXEDTO8;
    return !!(fmt->dwFlags & flags);
}