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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ GetDWBE (int /*<<< orphan*/  const*) ; 
 scalar_t__ INT32_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static inline int ReadBEInt32ToUInt32( const uint8_t *p, uint32_t *i_out )
{
    uint32_t i_value = GetDWBE( p );

    if( i_value > INT32_MAX ) return VLC_EGENERIC;

    *i_out = i_value;
    return VLC_SUCCESS;
}