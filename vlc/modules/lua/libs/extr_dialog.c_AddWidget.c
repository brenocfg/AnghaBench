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
typedef  int /*<<< orphan*/  extension_widget_t ;
struct TYPE_3__ {int /*<<< orphan*/  widgets; } ;
typedef  TYPE_1__ extension_dialog_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AddWidget( extension_dialog_t *p_dialog,
                       extension_widget_t *p_widget )
{
    ARRAY_APPEND( p_dialog->widgets, p_widget );
}