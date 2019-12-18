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
struct TYPE_3__ {scalar_t__ b_xa; } ;
typedef  TYPE_1__ iso9660_t ;

/* Variables and functions */
 scalar_t__ yep ; 

bool
iso9660_ifs_is_xa (const iso9660_t * p_iso)
{
  if (!p_iso) return false;
  return yep == p_iso->b_xa;
}