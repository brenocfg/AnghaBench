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
struct d3dx_top_level_parameter {void* update_version; struct d3dx_shared_data* shared_data; int /*<<< orphan*/  version_counter; } ;
struct d3dx_shared_data {void* update_version; } ;
struct d3dx_parameter {struct d3dx_top_level_parameter* top_level_param; } ;
typedef  void* ULONG64 ;

/* Variables and functions */
 void* next_update_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dirty(struct d3dx_parameter *param)
{
    struct d3dx_shared_data *shared_data;
    struct d3dx_top_level_parameter *top_param = param->top_level_param;
    ULONG64 new_update_version = next_update_version(top_param->version_counter);

    if ((shared_data = top_param->shared_data))
        shared_data->update_version = new_update_version;
    else
        top_param->update_version = new_update_version;
}