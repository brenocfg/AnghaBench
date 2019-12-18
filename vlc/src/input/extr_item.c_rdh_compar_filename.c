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
struct TYPE_5__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_6__ {TYPE_1__* p_item; } ;
typedef  TYPE_2__ input_item_node_t ;

/* Variables and functions */
 int rdh_compar_type (TYPE_1__*,TYPE_1__*) ; 
 int vlc_filenamecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdh_compar_filename(const void *a, const void *b)
{
    input_item_node_t *const *na = a, *const *nb = b;
    input_item_t *ia = (*na)->p_item, *ib = (*nb)->p_item;

    int i_ret = rdh_compar_type(ia, ib);
    if (i_ret != 0)
        return i_ret;

    return vlc_filenamecmp(ia->psz_name, ib->psz_name);
}