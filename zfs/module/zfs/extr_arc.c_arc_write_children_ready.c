#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* io_private; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {int /*<<< orphan*/  awcb_private; int /*<<< orphan*/  (* awcb_children_ready ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * awcb_buf; } ;
typedef  TYPE_2__ arc_write_callback_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arc_write_children_ready(zio_t *zio)
{
	arc_write_callback_t *callback = zio->io_private;
	arc_buf_t *buf = callback->awcb_buf;

	callback->awcb_children_ready(zio, buf, callback->awcb_private);
}