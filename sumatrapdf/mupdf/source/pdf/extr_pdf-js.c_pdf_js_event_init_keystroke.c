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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_keystroke_event ;
typedef  int /*<<< orphan*/  pdf_js ;

/* Variables and functions */

void pdf_js_event_init_keystroke(pdf_js *js, pdf_obj *target, pdf_keystroke_event *event) { }