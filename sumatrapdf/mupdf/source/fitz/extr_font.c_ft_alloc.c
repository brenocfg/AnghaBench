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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {scalar_t__ user; } ;
typedef  TYPE_1__* FT_Memory ;

/* Variables and functions */
 void* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_malloc_no_throw (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static void *ft_alloc(FT_Memory memory, long size)
{
	fz_context *ctx = (fz_context *) memory->user;
	return Memento_label(fz_malloc_no_throw(ctx, size), "ft_alloc");
}