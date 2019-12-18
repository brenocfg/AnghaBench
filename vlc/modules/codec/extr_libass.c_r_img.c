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
typedef  int /*<<< orphan*/  rectangle_t ;
struct TYPE_3__ {scalar_t__ h; scalar_t__ dst_y; scalar_t__ w; scalar_t__ dst_x; } ;
typedef  TYPE_1__ ASS_Image ;

/* Variables and functions */
 int /*<<< orphan*/  r_create (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rectangle_t r_img( const ASS_Image *p_img )
{
    return r_create( p_img->dst_x, p_img->dst_y, p_img->dst_x+p_img->w, p_img->dst_y+p_img->h );
}