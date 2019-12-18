#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int i_pid; } ;
typedef  TYPE_1__ pmt_map_t ;

/* Variables and functions */

__attribute__((used)) static int pmtcompare( const void *pa, const void *pb )
{
    int id1 = ((pmt_map_t *)pa)->i_pid;
    int id2 = ((pmt_map_t *)pb)->i_pid;

    return id1 - id2;
}