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
struct TYPE_4__ {int /*<<< orphan*/  app_name; struct TYPE_4__* link_source_name; struct TYPE_4__* link_type_name; struct TYPE_4__* source_name; struct TYPE_4__* type_name; } ;
typedef  TYPE_1__ ps_struct_t ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void free_structure(ps_struct_t *ps_struct)
{
    HeapFree(GetProcessHeap(), 0, ps_struct->type_name);
    HeapFree(GetProcessHeap(), 0, ps_struct->source_name);
    HeapFree(GetProcessHeap(), 0, ps_struct->link_type_name);
    HeapFree(GetProcessHeap(), 0, ps_struct->link_source_name);
    CoTaskMemFree(ps_struct->app_name);
    HeapFree(GetProcessHeap(), 0, ps_struct);
}