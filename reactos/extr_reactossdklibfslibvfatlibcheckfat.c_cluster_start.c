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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int off_t ;
struct TYPE_3__ {int data_start; scalar_t__ cluster_size; } ;
typedef  TYPE_1__ DOS_FS ;

/* Variables and functions */

off_t cluster_start(DOS_FS * fs, uint32_t cluster)
{
    return fs->data_start + ((off_t)cluster - 2) * (uint64_t)fs->cluster_size;
}