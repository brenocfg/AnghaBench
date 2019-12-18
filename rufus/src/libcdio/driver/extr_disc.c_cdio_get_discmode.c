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
typedef  int /*<<< orphan*/  discmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_discmode ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_DISC_MODE_ERROR ; 
 int /*<<< orphan*/  CDIO_DISC_MODE_NO_INFO ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

discmode_t
cdio_get_discmode (CdIo_t *cd_obj)
{
  if (!cd_obj) return CDIO_DISC_MODE_ERROR;
  
  if (cd_obj->op.get_discmode) {
    return cd_obj->op.get_discmode (cd_obj->env);
  } else {
    return CDIO_DISC_MODE_NO_INFO;
  }
}