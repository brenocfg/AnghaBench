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
typedef  int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void opj_read_bytes_LE(const OPJ_BYTE * p_buffer, OPJ_UINT32 * p_value,
                       OPJ_UINT32 p_nb_bytes)
{
    OPJ_BYTE * l_data_ptr = ((OPJ_BYTE *) p_value) + p_nb_bytes - 1;
    OPJ_UINT32 i;

    assert(p_nb_bytes > 0 && p_nb_bytes <= sizeof(OPJ_UINT32));

    *p_value = 0;
    for (i = 0; i < p_nb_bytes; ++i) {
        *(l_data_ptr--) = *(p_buffer++);
    }
}