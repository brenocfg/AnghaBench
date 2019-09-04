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
typedef  enum wined3d_decl_usage { ____Placeholder_wined3d_decl_usage } wined3d_decl_usage ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * semantic_names ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wined3d_decl_usage shader_usage_from_semantic_name(const char *name)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(semantic_names); ++i)
    {
        if (!strcmp(name, semantic_names[i]))
            return i;
    }

    return ~0U;
}