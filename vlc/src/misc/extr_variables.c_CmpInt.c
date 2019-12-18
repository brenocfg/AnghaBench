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
struct TYPE_4__ {scalar_t__ i_int; } ;
typedef  TYPE_1__ vlc_value_t ;

/* Variables and functions */

__attribute__((used)) static int CmpInt( vlc_value_t v, vlc_value_t w )
{
    return v.i_int == w.i_int ? 0 : v.i_int > w.i_int ? 1 : -1;
}