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
struct TYPE_3__ {int /*<<< orphan*/  resolutions; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ opj_tcd_tilecomp_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (int /*<<< orphan*/ ) ; 

void free_tilec(opj_tcd_tilecomp_t * l_tilec)
{
    opj_free(l_tilec->data);
    opj_free(l_tilec->resolutions);
}