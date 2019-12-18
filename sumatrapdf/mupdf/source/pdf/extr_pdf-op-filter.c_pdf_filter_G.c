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
typedef  int /*<<< orphan*/  pdf_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_filter_CS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_filter_SC_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,float*) ; 

__attribute__((used)) static void
pdf_filter_G(fz_context *ctx, pdf_processor *proc, float g)
{
	float color[1] = { g };
	pdf_filter_CS(ctx, proc, "DeviceGray", fz_device_gray(ctx));
	pdf_filter_SC_color(ctx, proc, 1, color);
}