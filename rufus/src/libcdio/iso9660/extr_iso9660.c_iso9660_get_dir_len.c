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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ iso9660_dir_t ;

/* Variables and functions */

uint8_t
iso9660_get_dir_len(const iso9660_dir_t *idr)
{
  if (NULL == idr) return 0;
  return idr->length;
}