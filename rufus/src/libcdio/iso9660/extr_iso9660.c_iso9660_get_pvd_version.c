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
struct TYPE_3__ {int version; } ;
typedef  TYPE_1__ iso9660_pvd_t ;

/* Variables and functions */

int
iso9660_get_pvd_version(const iso9660_pvd_t *pvd)
{
  if (NULL == pvd) return 0;
  return pvd->version;
}