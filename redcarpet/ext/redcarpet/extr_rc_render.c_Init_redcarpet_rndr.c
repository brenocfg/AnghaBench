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
 void* rb_cObject ; 
 void* rb_cRenderBase ; 
 void* rb_cRenderHTML ; 
 void* rb_cRenderHTML_TOC ; 
 int /*<<< orphan*/  rb_define_alloc_func (void*,int /*<<< orphan*/ ) ; 
 void* rb_define_class_under (void*,char*,void*) ; 
 int /*<<< orphan*/  rb_define_method (void*,char*,int /*<<< orphan*/ ,int) ; 
 void* rb_define_module_under (void*,char*) ; 
 void* rb_mRedcarpet ; 
 void* rb_mRender ; 
 void* rb_mSmartyPants ; 
 int /*<<< orphan*/  rb_redcarpet_html_init ; 
 int /*<<< orphan*/  rb_redcarpet_htmltoc_init ; 
 int /*<<< orphan*/  rb_redcarpet_rbase_alloc ; 
 int /*<<< orphan*/  rb_redcarpet_rbase_init ; 
 int /*<<< orphan*/  rb_redcarpet_smartypants_render ; 

void Init_redcarpet_rndr()
{
	rb_mRender = rb_define_module_under(rb_mRedcarpet, "Render");

	rb_cRenderBase = rb_define_class_under(rb_mRender, "Base", rb_cObject);
	rb_define_alloc_func(rb_cRenderBase, rb_redcarpet_rbase_alloc);
	rb_define_method(rb_cRenderBase, "initialize", rb_redcarpet_rbase_init, 0);

	rb_cRenderHTML = rb_define_class_under(rb_mRender, "HTML", rb_cRenderBase);
	rb_define_method(rb_cRenderHTML, "initialize", rb_redcarpet_html_init, -1);

	rb_cRenderHTML_TOC = rb_define_class_under(rb_mRender, "HTML_TOC", rb_cRenderBase);
	rb_define_method(rb_cRenderHTML_TOC, "initialize", rb_redcarpet_htmltoc_init, -1);

	rb_mSmartyPants = rb_define_module_under(rb_mRender, "SmartyPants");
	rb_define_method(rb_mSmartyPants, "postprocess", rb_redcarpet_smartypants_render, 1);
}