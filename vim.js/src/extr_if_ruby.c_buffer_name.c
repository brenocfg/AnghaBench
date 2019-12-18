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
struct TYPE_3__ {scalar_t__ b_ffname; } ;
typedef  TYPE_1__ buf_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Qnil ; 
 TYPE_1__* get_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_str_new2 (char*) ; 

__attribute__((used)) static VALUE buffer_name(VALUE self)
{
    buf_T *buf = get_buf(self);

    return buf->b_ffname ? rb_str_new2((char *)buf->b_ffname) : Qnil;
}