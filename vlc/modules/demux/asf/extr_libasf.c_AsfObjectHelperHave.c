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

__attribute__((used)) static inline bool AsfObjectHelperHave( const uint8_t *p_peek, size_t i_peek, const uint8_t *p_current, size_t i_wanted )
{
    if( i_wanted > i_peek )
        return false;
    return &p_current[i_wanted] <= &p_peek[i_peek];
}