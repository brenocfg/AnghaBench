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
typedef  void* OPJ_SIZE_T ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_ARG_NOT_USED (void*) ; 

OPJ_SIZE_T opj_stream_default_read(void * p_buffer, OPJ_SIZE_T p_nb_bytes,
                                   void * p_user_data)
{
    OPJ_ARG_NOT_USED(p_buffer);
    OPJ_ARG_NOT_USED(p_nb_bytes);
    OPJ_ARG_NOT_USED(p_user_data);
    return (OPJ_SIZE_T) - 1;
}