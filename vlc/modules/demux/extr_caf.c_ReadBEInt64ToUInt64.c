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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ GetQWBE (int /*<<< orphan*/  const*) ; 
 scalar_t__ INT64_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static inline int ReadBEInt64ToUInt64( const uint8_t *p, uint64_t *i_out )
{
    uint64_t i_value = GetQWBE( p );

    if( i_value > INT64_MAX ) return VLC_EGENERIC;

    *i_out = i_value;
    return VLC_SUCCESS;
}