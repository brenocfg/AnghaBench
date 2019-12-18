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
typedef  int /*<<< orphan*/  opj_stream_private_t ;
typedef  int /*<<< orphan*/  opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_build_decoder(opj_j2k_t * p_j2k,
                                      opj_stream_private_t *p_stream,
                                      opj_event_mgr_t * p_manager)
{
    /* add here initialization of cp
       copy paste of setup_decoder */
    (void)p_j2k;
    (void)p_stream;
    (void)p_manager;
    return OPJ_TRUE;
}