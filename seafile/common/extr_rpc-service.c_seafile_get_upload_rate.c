#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sync_mgr; } ;
struct TYPE_3__ {int last_sent_bytes; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 TYPE_2__* seaf ; 

int
seafile_get_upload_rate(GError **error)
{
    return seaf->sync_mgr->last_sent_bytes;
}