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
struct handle_wrapper {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */

__attribute__((used)) static ULONG handle_getsize(struct handle_wrapper *handle)
{
    return handle->size;
}