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
struct TYPE_4__ {scalar_t__ refs; } ;
struct TYPE_5__ {scalar_t__ store_key_refs; TYPE_1__ storable; } ;
typedef  TYPE_2__ fz_key_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_key_storable_needs_reaping(fz_context *ctx, const fz_key_storable *ks)
{
	return ks == NULL ? 0 : (ks->store_key_refs == ks->storable.refs);
}