#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int b_interlace; scalar_t__ i_res; int /*<<< orphan*/  i_pps; int /*<<< orphan*/ * p_pps; int /*<<< orphan*/  i_sps; int /*<<< orphan*/ * p_sps; } ;

/* Variables and functions */
 int AVCI_ENTRIES ; 
 TYPE_1__* AVCi_lookup_table ; 

__attribute__((used)) static inline bool AVCi_lookup(uint16_t i_res, bool b_i,
                               const uint8_t **pp_sps, uint8_t *pi_sps,
                               const uint8_t **pp_pps, uint8_t *pi_pps)
{
    for(int i=0; i<AVCI_ENTRIES; i++)
    {
        if(AVCi_lookup_table[i].b_interlace == b_i && AVCi_lookup_table[i].i_res == i_res)
        {
            *pp_sps = AVCi_lookup_table[i].p_sps;
            *pi_sps = AVCi_lookup_table[i].i_sps;
            *pp_pps = AVCi_lookup_table[i].p_pps;
            *pi_pps = AVCi_lookup_table[i].i_pps;
            return true;
        }
    }
    return false;
}