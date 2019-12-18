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
 int A52CheckSync (int /*<<< orphan*/  const*,int*,unsigned int*,int) ; 

__attribute__((used)) static int A52CheckSyncProbe( const uint8_t *p_peek, unsigned *pi_samples )
{
    bool b_dummy;
    return A52CheckSync( p_peek, &b_dummy, pi_samples, false );
}