#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  u_joliet_level; } ;
typedef  TYPE_1__ generic_img_private_t ;
struct TYPE_5__ {scalar_t__ env; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */

uint8_t
cdio_get_joliet_level(const CdIo_t *p_cdio)
{
  if (!p_cdio) return 0;
  {
    const generic_img_private_t *p_env
      = (generic_img_private_t *) (p_cdio->env);
    return p_env->u_joliet_level;
  }
}