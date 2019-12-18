#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_5__ {TYPE_1__ illuminant; int /*<<< orphan*/  platform; int /*<<< orphan*/  magic; int /*<<< orphan*/  pcs; int /*<<< orphan*/  colorSpace; int /*<<< orphan*/  deviceClass; int /*<<< orphan*/  version; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ icHeader ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_byte_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_append_int32_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_header(fz_context *ctx, fz_buffer *buffer, icHeader *header)
{
	fz_append_int32_be(ctx, buffer, header->size);
	fz_append_byte_n(ctx, buffer, 0, 4);
	fz_append_int32_be(ctx, buffer, header->version);
	fz_append_int32_be(ctx, buffer, header->deviceClass);
	fz_append_int32_be(ctx, buffer, header->colorSpace);
	fz_append_int32_be(ctx, buffer, header->pcs);
	fz_append_byte_n(ctx, buffer, 0, 12);
	fz_append_int32_be(ctx, buffer, header->magic);
	fz_append_int32_be(ctx, buffer, header->platform);
	fz_append_byte_n(ctx, buffer, 0, 24);
	fz_append_int32_be(ctx, buffer, header->illuminant.X);
	fz_append_int32_be(ctx, buffer, header->illuminant.Y);
	fz_append_int32_be(ctx, buffer, header->illuminant.Z);
	fz_append_byte_n(ctx, buffer, 0, 48);
}