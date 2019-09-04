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
struct ifacepsredirect_data {int dummy; } ;
struct guid_index {int data_offset; } ;
struct TYPE_3__ {scalar_t__ ifaceps_section; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ACTIVATION_CONTEXT ;

/* Variables and functions */

__attribute__((used)) static inline struct ifacepsredirect_data *get_ifaceps_data(ACTIVATION_CONTEXT *actctx, struct guid_index *index)
{
    return (struct ifacepsredirect_data*)((BYTE*)actctx->ifaceps_section + index->data_offset);
}