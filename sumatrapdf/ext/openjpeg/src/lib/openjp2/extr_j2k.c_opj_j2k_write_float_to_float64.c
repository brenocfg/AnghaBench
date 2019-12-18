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
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_FLOAT64 ;
typedef  int /*<<< orphan*/  OPJ_FLOAT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  opj_write_double (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void  opj_j2k_write_float_to_float64(const void * p_src_data,
        void * p_dest_data, OPJ_UINT32 p_nb_elem)
{
    OPJ_BYTE * l_dest_data = (OPJ_BYTE *) p_dest_data;
    OPJ_FLOAT32 * l_src_data = (OPJ_FLOAT32 *) p_src_data;
    OPJ_UINT32 i;
    OPJ_FLOAT64 l_temp;

    for (i = 0; i < p_nb_elem; ++i) {
        l_temp = (OPJ_FLOAT64) * (l_src_data++);

        opj_write_double(l_dest_data, l_temp);

        l_dest_data += sizeof(OPJ_FLOAT64);
    }
}