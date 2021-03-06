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
struct TYPE_3__ {int byte_padding; } ;
typedef  TYPE_1__ fz_icc_tag ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_byte_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_append_int32_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  icSigTextType ; 

__attribute__((used)) static void
add_text_tag(fz_context *ctx, fz_buffer *buf, const char text[], fz_icc_tag tag_list[], int curr_tag)
{
	fz_append_int32_be(ctx, buf, icSigTextType);
	fz_append_byte_n(ctx, buf, 0, 4);
	fz_append_string(ctx, buf, text);
	fz_append_byte(ctx, buf, 0);
	fz_append_byte_n(ctx, buf, 0, tag_list[curr_tag].byte_padding);
}