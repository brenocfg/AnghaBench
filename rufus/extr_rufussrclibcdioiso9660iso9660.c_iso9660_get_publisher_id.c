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
struct TYPE_3__ {int /*<<< orphan*/  publisher_id; } ;
typedef  TYPE_1__ iso9660_pvd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_MAX_PUBLISHER_ID ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_trail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
iso9660_get_publisher_id(const iso9660_pvd_t *pvd)
{
  if (NULL==pvd) return NULL;
  return strdup(strip_trail(pvd->publisher_id, ISO_MAX_PUBLISHER_ID));
}