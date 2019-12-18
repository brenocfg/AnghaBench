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

/* Variables and functions */
 int /*<<< orphan*/  Init_redcarpet_rndr () ; 
 int /*<<< orphan*/  rb_cMarkdown ; 
 int /*<<< orphan*/  rb_cObject ; 
 int /*<<< orphan*/  rb_define_class_under (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_define_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_define_module (char*) ; 
 int /*<<< orphan*/  rb_define_singleton_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_mRedcarpet ; 
 int /*<<< orphan*/  rb_redcarpet_md__new ; 
 int /*<<< orphan*/  rb_redcarpet_md_render ; 

__attribute__((visibility("default")))
void Init_redcarpet()
{
	rb_mRedcarpet = rb_define_module("Redcarpet");

	rb_cMarkdown = rb_define_class_under(rb_mRedcarpet, "Markdown", rb_cObject);
	rb_define_singleton_method(rb_cMarkdown, "new", rb_redcarpet_md__new, -1);
	rb_define_method(rb_cMarkdown, "render", rb_redcarpet_md_render, 1);

	Init_redcarpet_rndr();
}