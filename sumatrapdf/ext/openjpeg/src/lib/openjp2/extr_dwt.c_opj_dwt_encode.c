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
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_dwt_encode_1 ; 
 int /*<<< orphan*/  opj_dwt_encode_procedure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

OPJ_BOOL opj_dwt_encode(opj_tcd_tilecomp_t * tilec)
{
    return opj_dwt_encode_procedure(tilec, opj_dwt_encode_1);
}