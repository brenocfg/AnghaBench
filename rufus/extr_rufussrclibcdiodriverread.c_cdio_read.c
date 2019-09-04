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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (int /*<<< orphan*/ ,void*,size_t) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_OP_UNINIT ; 
 int /*<<< orphan*/  DRIVER_OP_UNSUPPORTED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t
cdio_read (const CdIo_t *p_cdio, void *p_buf, size_t i_size)
{
  if (!p_cdio) return DRIVER_OP_UNINIT;

  if (p_cdio->op.read)
    return (p_cdio->op.read) (p_cdio->env, p_buf, i_size);
  return DRIVER_OP_UNSUPPORTED;
}