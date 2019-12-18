#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_set_threads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OPJ_BOOL opj_jp2_set_threads(opj_jp2_t *jp2, OPJ_UINT32 num_threads)
{
    return opj_j2k_set_threads(jp2->j2k, num_threads);
}