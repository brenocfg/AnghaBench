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
struct TYPE_4__ {int /*<<< orphan*/  of_dtable; int /*<<< orphan*/  ml_dtable; int /*<<< orphan*/  ll_dtable; int /*<<< orphan*/  literals_dtable; } ;
typedef  TYPE_1__ frame_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_free_dtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_free_dtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_frame_context(frame_context_t *const context) {
    HUF_free_dtable(&context->literals_dtable);

    FSE_free_dtable(&context->ll_dtable);
    FSE_free_dtable(&context->ml_dtable);
    FSE_free_dtable(&context->of_dtable);

    memset(context, 0, sizeof(frame_context_t));
}