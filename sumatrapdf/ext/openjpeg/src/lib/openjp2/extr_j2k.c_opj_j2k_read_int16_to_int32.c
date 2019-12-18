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
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_INT16 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  opj_read_bytes (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static void  opj_j2k_read_int16_to_int32(const void * p_src_data,
        void * p_dest_data, OPJ_UINT32 p_nb_elem)
{
    OPJ_BYTE * l_src_data = (OPJ_BYTE *) p_src_data;
    OPJ_INT32 * l_dest_data = (OPJ_INT32 *) p_dest_data;
    OPJ_UINT32 i;
    OPJ_UINT32 l_temp;

    for (i = 0; i < p_nb_elem; ++i) {
        opj_read_bytes(l_src_data, &l_temp, 2);

        l_src_data += sizeof(OPJ_INT16);

        *(l_dest_data++) = (OPJ_INT32) l_temp;
    }
}