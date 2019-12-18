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
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int RenderYadif (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int RenderYadifSingle( filter_t *p_filter, picture_t *p_dst, picture_t *p_src )
{
    return RenderYadif( p_filter, p_dst, p_src, 0, 0 );
}