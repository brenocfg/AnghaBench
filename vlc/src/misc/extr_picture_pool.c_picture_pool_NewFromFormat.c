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
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * picture_NewFromFormat (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_New (unsigned int,int /*<<< orphan*/ **) ; 

picture_pool_t *picture_pool_NewFromFormat(const video_format_t *fmt,
                                           unsigned count)
{
    picture_t *picture[count ? count : 1];
    unsigned i;

    for (i = 0; i < count; i++) {
        picture[i] = picture_NewFromFormat(fmt);
        if (picture[i] == NULL)
            goto error;
    }

    picture_pool_t *pool = picture_pool_New(count, picture);
    if (!pool)
        goto error;

    return pool;

error:
    while (i > 0)
        picture_Release(picture[--i]);
    return NULL;
}