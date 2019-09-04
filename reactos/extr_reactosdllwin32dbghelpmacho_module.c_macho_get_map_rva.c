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
struct image_section_map {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */

DWORD_PTR macho_get_map_rva(const struct image_section_map* ism)
{
    return 0;
}