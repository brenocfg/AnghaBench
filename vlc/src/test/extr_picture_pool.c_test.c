#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_7__ {void* p_pixels; } ;

/* Variables and functions */
 int PICTURES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fmt ; 
 int /*<<< orphan*/  picture_Hold (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 
 TYPE_2__* picture_pool_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_NewFromFormat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_Reserve (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* picture_pool_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pool ; 
 int /*<<< orphan*/ * reserve ; 

__attribute__((used)) static void test(bool zombie)
{
    picture_t *pics[PICTURES];

    pool = picture_pool_NewFromFormat(&fmt, PICTURES);
    assert(pool != NULL);

    for (unsigned i = 0; i < PICTURES; i++) {
        pics[i] = picture_pool_Get(pool);
        assert(pics[i] != NULL);
    }

    for (unsigned i = 0; i < PICTURES; i++)
        assert(picture_pool_Get(pool) == NULL);

    // Reserve currently assumes that all pictures are free (or reserved).
    //assert(picture_pool_Reserve(pool, 1) == NULL);

    for (unsigned i = 0; i < PICTURES / 2; i++)
        picture_Hold(pics[i]);

    for (unsigned i = 0; i < PICTURES / 2; i++)
        picture_Release(pics[i]);

    for (unsigned i = 0; i < PICTURES; i++) {
        void *plane = pics[i]->p[0].p_pixels;
        assert(plane != NULL);
        picture_Release(pics[i]);

        pics[i] = picture_pool_Get(pool);
        assert(pics[i] != NULL);
        assert(pics[i]->p[0].p_pixels == plane);
    }

    for (unsigned i = 0; i < PICTURES; i++)
        picture_Release(pics[i]);

    for (unsigned i = 0; i < PICTURES; i++) {
        pics[i] = picture_pool_Wait(pool);
        assert(pics[i] != NULL);
    }

    for (unsigned i = 0; i < PICTURES; i++)
        picture_Release(pics[i]);

    reserve = picture_pool_Reserve(pool, PICTURES / 2);
    assert(reserve != NULL);

    for (unsigned i = 0; i < PICTURES / 2; i++) {
        pics[i] = picture_pool_Get(pool);
        assert(pics[i] != NULL);
    }

    for (unsigned i = PICTURES / 2; i < PICTURES; i++) {
        assert(picture_pool_Get(pool) == NULL);
        pics[i] = picture_pool_Get(reserve);
        assert(pics[i] != NULL);
    }

    if (!zombie)
        for (unsigned i = 0; i < PICTURES; i++)
            picture_Release(pics[i]);

    picture_pool_Release(reserve);
    picture_pool_Release(pool);

    if (zombie)
        for (unsigned i = 0; i < PICTURES; i++)
            picture_Release(pics[i]);
}