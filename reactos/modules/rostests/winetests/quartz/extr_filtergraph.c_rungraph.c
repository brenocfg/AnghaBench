#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  IFilterGraph2 ;

/* Variables and functions */
 int /*<<< orphan*/  test_basic_video (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_media_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_media_seeking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_state_change (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rungraph(IFilterGraph2 *graph)
{
    test_basic_video(graph);
    test_media_seeking(graph);
    test_state_change(graph);
    test_media_event(graph);
}