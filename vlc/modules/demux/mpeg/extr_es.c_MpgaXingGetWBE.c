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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MpgaXingSkip (int /*<<< orphan*/  const**,int*,int) ; 

__attribute__((used)) static uint16_t MpgaXingGetWBE( const uint8_t **pp_xing, int *pi_xing, uint16_t i_default )
{
    if( *pi_xing < 2 )
        return i_default;

    uint16_t v = GetWBE( *pp_xing );

    MpgaXingSkip( pp_xing, pi_xing, 2 );

    return v;
}