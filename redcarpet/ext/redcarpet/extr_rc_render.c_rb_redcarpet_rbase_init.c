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
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Qnil ; 
 int /*<<< orphan*/  rb_cRenderBase ; 
 int /*<<< orphan*/  rb_redcarpet__overload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE rb_redcarpet_rbase_init(VALUE self)
{
	rb_redcarpet__overload(self, rb_cRenderBase);
	return Qnil;
}