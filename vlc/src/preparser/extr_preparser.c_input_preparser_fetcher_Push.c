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
struct TYPE_3__ {scalar_t__ fetcher; } ;
typedef  TYPE_1__ input_preparser_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_meta_request_option_t ;
typedef  int /*<<< orphan*/  input_fetcher_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_fetcher_Push (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*) ; 

void input_preparser_fetcher_Push( input_preparser_t *preparser,
    input_item_t *item, input_item_meta_request_option_t options,
    const input_fetcher_callbacks_t *cbs, void *cbs_userdata )
{
    if( preparser->fetcher )
        input_fetcher_Push( preparser->fetcher, item, options,
                            cbs, cbs_userdata );
}