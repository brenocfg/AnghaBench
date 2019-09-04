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
struct wined3d_vertex_element {int /*<<< orphan*/  usage_idx; int /*<<< orphan*/  usage; int /*<<< orphan*/  method; int /*<<< orphan*/  instance_data_step_rate; int /*<<< orphan*/  input_slot_class; int /*<<< orphan*/  output_slot; int /*<<< orphan*/  offset; int /*<<< orphan*/  input_slot; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debug_d3ddeclmethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3ddeclusage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dinput_classification (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_wined3d_vertex_element(const struct wined3d_vertex_element *element)
{
    TRACE("                 format: %s (%#x)\n", debug_d3dformat(element->format), element->format);
    TRACE("             input_slot: %u\n", element->input_slot);
    TRACE("                 offset: %u\n", element->offset);
    TRACE("            output_slot: %u\n", element->output_slot);
    TRACE("       input slot class: %s\n", debug_d3dinput_classification(element->input_slot_class));
    TRACE("instance data step rate: %u\n", element->instance_data_step_rate);
    TRACE("                 method: %s (%#x)\n", debug_d3ddeclmethod(element->method), element->method);
    TRACE("                  usage: %s (%#x)\n", debug_d3ddeclusage(element->usage), element->usage);
    TRACE("              usage_idx: %u\n", element->usage_idx);
}