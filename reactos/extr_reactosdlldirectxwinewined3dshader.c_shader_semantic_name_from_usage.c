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
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 char const** semantic_names ; 

__attribute__((used)) static const char *shader_semantic_name_from_usage(enum wined3d_decl_usage usage)
{
    if (usage >= ARRAY_SIZE(semantic_names))
    {
        FIXME("Unrecognized usage %#x.\n", usage);
        return "UNRECOGNIZED";
    }

    return semantic_names[usage];
}