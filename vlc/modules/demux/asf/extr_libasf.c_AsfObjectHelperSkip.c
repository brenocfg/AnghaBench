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

/* Variables and functions */
 scalar_t__ AsfObjectHelperHave (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline void AsfObjectHelperSkip( const uint8_t *p_peek, size_t i_peek, uint8_t **pp_data, size_t i_wanted )
{
    if( AsfObjectHelperHave( p_peek, i_peek, *pp_data, i_wanted ) )
        *pp_data += i_wanted;
    else
        *pp_data = (uint8_t*)&p_peek[i_peek];
}