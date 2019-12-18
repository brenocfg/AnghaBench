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
typedef  int /*<<< orphan*/  fz_pixmap ;
struct TYPE_4__ {int refs; int n; int /*<<< orphan*/ ** comp; } ;
typedef  TYPE_1__ fz_halftone ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_halftone *
fz_new_halftone(fz_context *ctx, int comps)
{
	fz_halftone *ht;
	int i;

	ht = Memento_label(fz_malloc(ctx, sizeof(fz_halftone) + (comps-1)*sizeof(fz_pixmap *)), "fz_halftone");
	ht->refs = 1;
	ht->n = comps;
	for (i = 0; i < comps; i++)
		ht->comp[i] = NULL;

	return ht;
}