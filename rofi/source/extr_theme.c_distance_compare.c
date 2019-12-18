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
typedef  int gboolean ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ distance; scalar_t__ style; } ;
typedef  TYPE_1__ RofiDistance ;

/* Variables and functions */

__attribute__((used)) static gboolean distance_compare ( RofiDistance d, RofiDistance e )
{
    return d.type == e.type && d.distance == e.distance && d.style == e.style;
}