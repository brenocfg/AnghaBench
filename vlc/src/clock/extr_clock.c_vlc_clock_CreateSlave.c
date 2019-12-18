#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 TYPE_1__* vlc_clock_main_CreateSlave (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

vlc_clock_t *vlc_clock_CreateSlave(const vlc_clock_t *clock,
                                   enum es_format_category_e cat)
{
    return vlc_clock_main_CreateSlave(clock->owner, cat, NULL, NULL);
}