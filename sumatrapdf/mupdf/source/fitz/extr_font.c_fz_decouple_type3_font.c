#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* t3doc; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  free_resources (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void fz_decouple_type3_font(fz_context *ctx, fz_font *font, void *t3doc)
{
	if (!font || !t3doc || font->t3doc == NULL)
		return;

	if (font->t3doc != t3doc)
		fz_throw(ctx, FZ_ERROR_GENERIC, "can't decouple type3 font from a different doc");

	font->t3doc = NULL;
	free_resources(ctx, font);
}