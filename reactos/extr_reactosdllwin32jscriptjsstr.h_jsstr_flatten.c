#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  const* buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  const* buf; } ;

/* Variables and functions */
 TYPE_2__* jsstr_as_heap (int /*<<< orphan*/ *) ; 
 TYPE_1__* jsstr_as_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_as_rope (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_heap (int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_is_inline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* jsstr_rope_flatten (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const WCHAR *jsstr_flatten(jsstr_t *str)
{
    return jsstr_is_inline(str) ? jsstr_as_inline(str)->buf
        : jsstr_is_heap(str) ? jsstr_as_heap(str)->buf
        : jsstr_rope_flatten(jsstr_as_rope(str));
}