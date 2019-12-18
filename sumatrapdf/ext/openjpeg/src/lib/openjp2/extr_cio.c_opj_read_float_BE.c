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
typedef  int /*<<< orphan*/  OPJ_FLOAT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void opj_read_float_BE(const OPJ_BYTE * p_buffer, OPJ_FLOAT32 * p_value)
{
    OPJ_BYTE * l_data_ptr = ((OPJ_BYTE *) p_value);
    memcpy(l_data_ptr, p_buffer, sizeof(OPJ_FLOAT32));
}