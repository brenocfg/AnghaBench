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

/* Variables and functions */
 int PICTURES ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fmt ; 
 int picture_pool_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_NewFromFormat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_Reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pool ; 
 int /*<<< orphan*/ * reserve ; 
 int /*<<< orphan*/  test (int) ; 
 int /*<<< orphan*/  video_format_Setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

int main(void)
{
    video_format_Setup(&fmt, VLC_CODEC_I420, 320, 200, 320, 200, 1, 1);

    pool = picture_pool_NewFromFormat(&fmt, PICTURES);
    assert(pool != NULL);
    assert(picture_pool_GetSize(pool) == PICTURES);

    reserve = picture_pool_Reserve(pool, PICTURES / 2);
    assert(reserve != NULL);

    picture_pool_Release(reserve);
    picture_pool_Release(pool);

    test(false);
    test(true);

    return 0;
}