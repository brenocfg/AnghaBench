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
 int /*<<< orphan*/  BasicFilter_UpdateVAFilterParams ; 
 int /*<<< orphan*/ * Filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *
BasicFilter(filter_t * filter, picture_t * src)
{
    picture_t *const    dest =
        Filter(filter, src, BasicFilter_UpdateVAFilterParams, NULL, NULL);
    picture_Release(src);
    return dest;
}