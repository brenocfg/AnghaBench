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
typedef  int /*<<< orphan*/  CVPixelBufferRef ;

/* Variables and functions */
 int cvpxpic_attach_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ ,void*,unsigned int),void*) ; 
 int /*<<< orphan*/  cvpxpic_destroy_cb ; 

int cvpxpic_attach_with_cb(picture_t *p_pic, CVPixelBufferRef cvpx,
                           void (*on_released_cb)(CVPixelBufferRef, void *, unsigned),
                           void *on_released_data)
{
    return cvpxpic_attach_common(p_pic, cvpx, cvpxpic_destroy_cb, on_released_cb,
                                 on_released_data);
}