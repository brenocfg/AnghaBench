#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_minor; int /*<<< orphan*/  i_major; } ;
struct TYPE_6__ {TYPE_1__ brands; } ;
typedef  TYPE_2__ mp4mux_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp4mux_AddExtraBrand (TYPE_2__*,int /*<<< orphan*/ ) ; 

void mp4mux_SetBrand(mp4mux_handle_t *h, vlc_fourcc_t i_major, uint32_t i_minor)
{
    h->brands.i_major = i_major;
    h->brands.i_minor = i_minor;
    mp4mux_AddExtraBrand(h, i_major);
}