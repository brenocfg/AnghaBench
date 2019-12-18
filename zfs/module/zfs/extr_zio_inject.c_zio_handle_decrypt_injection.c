#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {scalar_t__ zi_cmd; } ;
struct TYPE_6__ {TYPE_2__ zi_record; int /*<<< orphan*/ * zi_spa; } ;
typedef  TYPE_1__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ ZINJECT_DECRYPT_FAULT ; 
 int /*<<< orphan*/  ZI_NO_DVA ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zio_match_handler (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

int
zio_handle_decrypt_injection(spa_t *spa, const zbookmark_phys_t *zb,
    uint64_t type, int error)
{
	int ret = 0;
	inject_handler_t *handler;

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {

		if (spa != handler->zi_spa ||
		    handler->zi_record.zi_cmd != ZINJECT_DECRYPT_FAULT)
			continue;

		if (zio_match_handler(zb, type, ZI_NO_DVA,
		    &handler->zi_record, error)) {
			ret = error;
			break;
		}
	}

	rw_exit(&inject_lock);
	return (ret);
}