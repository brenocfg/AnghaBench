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
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fread (void*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_SIZE_T opj_read_from_file(void * p_buffer, OPJ_SIZE_T p_nb_bytes,
                                     FILE * p_file)
{
    OPJ_SIZE_T l_nb_read = fread(p_buffer, 1, p_nb_bytes, p_file);
    return l_nb_read ? l_nb_read : (OPJ_SIZE_T) - 1;
}