#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  item; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ input_preparser_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReqRelease(input_preparser_req_t *req)
{
    if (vlc_atomic_rc_dec(&req->rc))
    {
        input_item_Release(req->item);
        free(req);
    }
}