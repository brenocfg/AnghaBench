#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {scalar_t__ destroy; int /*<<< orphan*/ * opaque; } ;
struct TYPE_6__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ picture_priv_t ;
struct TYPE_7__ {int /*<<< orphan*/ ** picture; } ;
typedef  TYPE_3__ picture_pool_t ;

/* Variables and functions */
 int POOL_MAX ; 
 scalar_t__ picture_pool_ReleasePicture ; 

bool picture_pool_OwnsPic(picture_pool_t *pool, picture_t *pic)
{
    picture_priv_t *priv = (picture_priv_t *)pic;

    while (priv->gc.destroy != picture_pool_ReleasePicture) {
        if (priv->gc.opaque == NULL)
            return false; /* not a pooled picture */

        pic = priv->gc.opaque;
        priv = (picture_priv_t *)pic;
    }

    do {
        uintptr_t sys = (uintptr_t)priv->gc.opaque;
        picture_pool_t *picpool = (void *)(sys & ~(POOL_MAX - 1));

        if (pool == picpool)
            return true;

        pic = picpool->picture[sys & (POOL_MAX - 1 )];
        priv = (picture_priv_t *)pic;
    } while (priv->gc.destroy == picture_pool_ReleasePicture);

    return false;
}