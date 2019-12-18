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
typedef  int /*<<< orphan*/ * gpointer ;
typedef  int /*<<< orphan*/  WTEvent ;

/* Variables and functions */
 int /*<<< orphan*/  wt_event_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_event_cb (gpointer data, gpointer user_data)
{
    WTEvent *event = data;
    wt_event_free (event);
}