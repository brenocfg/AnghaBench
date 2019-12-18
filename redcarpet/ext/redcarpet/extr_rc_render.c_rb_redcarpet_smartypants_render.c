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
typedef  int /*<<< orphan*/  uint8_t ;
struct buf {int /*<<< orphan*/  size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Check_Type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_STRING ; 
 struct buf* bufnew (int) ; 
 int /*<<< orphan*/  bufrelease (struct buf*) ; 
 int /*<<< orphan*/  rb_enc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_enc_str_new (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhtml_smartypants (struct buf*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE rb_redcarpet_smartypants_render(VALUE self, VALUE text)
{
	VALUE result;
	struct buf *output_buf;

	Check_Type(text, T_STRING);

	output_buf = bufnew(128);

	sdhtml_smartypants(output_buf, (const uint8_t*)RSTRING_PTR(text), RSTRING_LEN(text));
	result = rb_enc_str_new((const char*)output_buf->data, output_buf->size, rb_enc_get(text));

	bufrelease(output_buf);
	return result;
}