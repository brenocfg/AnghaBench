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
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dr_dbuf; } ;
typedef  TYPE_2__ dbuf_dirty_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbuf_write_ready (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_write_override_ready(zio_t *zio)
{
	dbuf_dirty_record_t *dr = zio->io_private;
	dmu_buf_impl_t *db = dr->dr_dbuf;

	dbuf_write_ready(zio, NULL, db);
}