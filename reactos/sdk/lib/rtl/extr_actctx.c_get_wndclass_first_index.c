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
struct string_index {int dummy; } ;
struct TYPE_5__ {TYPE_1__* wndclass_section; } ;
struct TYPE_4__ {int index_offset; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ ACTIVATION_CONTEXT ;

/* Variables and functions */

__attribute__((used)) static inline struct string_index *get_wndclass_first_index(ACTIVATION_CONTEXT *actctx)
{
    return (struct string_index*)((BYTE*)actctx->wndclass_section + actctx->wndclass_section->index_offset);
}