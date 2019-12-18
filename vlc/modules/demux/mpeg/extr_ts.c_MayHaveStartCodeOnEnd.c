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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bool MayHaveStartCodeOnEnd( const uint8_t *p_buf, size_t i_buf )
{
    assert(i_buf > 2);
    return !( *(--p_buf) > 1 || *(--p_buf) > 0 || *(--p_buf) > 0 );
}