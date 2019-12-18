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
typedef  int /*<<< orphan*/  OPJ_FLOAT64 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void opj_write_double_BE(OPJ_BYTE * p_buffer, OPJ_FLOAT64 p_value)
{
    const OPJ_BYTE * l_data_ptr = ((const OPJ_BYTE *) &p_value);
    memcpy(p_buffer, l_data_ptr, sizeof(OPJ_FLOAT64));
}