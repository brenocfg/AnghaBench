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

__attribute__((used)) static void BufLeToBe( uint8_t *p_out, const uint8_t *p_in, int i_in )
{
    int i;

    for( i = 0; i < i_in/2; i++  )
    {
        p_out[i*2] = p_in[i*2+1];
        p_out[i*2+1] = p_in[i*2];
    }
}