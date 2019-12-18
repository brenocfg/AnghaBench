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
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_3__ {int /*<<< orphan*/ * allocator_data; } ;
typedef  TYPE_1__ Dav1dPicture ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FreePicture(Dav1dPicture *data, void *cookie)
{
    picture_t *pic = data->allocator_data;
    decoder_t *dec = cookie;
    VLC_UNUSED(dec);
    picture_Release(pic);
}