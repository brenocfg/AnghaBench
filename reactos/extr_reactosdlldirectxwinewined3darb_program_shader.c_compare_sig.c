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
struct wined3d_shader_signature_element {scalar_t__ semantic_name; scalar_t__ semantic_idx; scalar_t__ sysval_semantic; scalar_t__ component_type; scalar_t__ register_idx; scalar_t__ mask; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int compare_sig(const struct wined3d_shader_signature *sig1, const struct wined3d_shader_signature *sig2)
{
    unsigned int i;
    int ret;

    if (sig1->element_count != sig2->element_count)
        return sig1->element_count < sig2->element_count ? -1 : 1;

    for (i = 0; i < sig1->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *e1, *e2;

        e1 = &sig1->elements[i];
        e2 = &sig2->elements[i];

        if (!e1->semantic_name || !e2->semantic_name)
        {
            /* Compare pointers, not contents. One string is NULL (element
             * does not exist), the other one is not NULL. */
            if (e1->semantic_name != e2->semantic_name)
                return e1->semantic_name < e2->semantic_name ? -1 : 1;
            continue;
        }

        if ((ret = strcmp(e1->semantic_name, e2->semantic_name)))
            return ret;
        if (e1->semantic_idx != e2->semantic_idx)
            return e1->semantic_idx < e2->semantic_idx ? -1 : 1;
        if (e1->sysval_semantic != e2->sysval_semantic)
            return e1->sysval_semantic < e2->sysval_semantic ? -1 : 1;
        if (e1->component_type != e2->component_type)
            return e1->component_type < e2->component_type ? -1 : 1;
        if (e1->register_idx != e2->register_idx)
            return e1->register_idx < e2->register_idx ? -1 : 1;
        if (e1->mask != e2->mask)
            return e1->mask < e2->mask ? -1 : 1;
    }
    return 0;
}