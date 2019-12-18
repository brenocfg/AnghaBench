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
struct TYPE_3__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ input_preparser_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReqHold(input_preparser_req_t *req)
{
    vlc_atomic_rc_inc(&req->rc);
}