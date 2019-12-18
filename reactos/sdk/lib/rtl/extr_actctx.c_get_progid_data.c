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
struct string_index {int data_offset; } ;
struct progidredirect_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ progid_section; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ACTIVATION_CONTEXT ;

/* Variables and functions */

__attribute__((used)) static inline struct progidredirect_data *get_progid_data(ACTIVATION_CONTEXT *actctx, const struct string_index *index)
{
    return (struct progidredirect_data*)((BYTE*)actctx->progid_section + index->data_offset);
}