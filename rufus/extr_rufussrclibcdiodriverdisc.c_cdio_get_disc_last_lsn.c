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
typedef  int /*<<< orphan*/  lsn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_disc_last_lsn ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_INVALID_LSN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

lsn_t 
cdio_get_disc_last_lsn(const CdIo_t *p_cdio)
{
  if (!p_cdio) return CDIO_INVALID_LSN;
  return p_cdio->op.get_disc_last_lsn (p_cdio->env);
}