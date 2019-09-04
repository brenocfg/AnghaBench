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
struct wine_rb_tree {int dummy; } ;
struct ffp_frag_desc {int /*<<< orphan*/  entry; int /*<<< orphan*/  settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int wine_rb_put (struct wine_rb_tree*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void add_ffp_frag_shader(struct wine_rb_tree *shaders, struct ffp_frag_desc *desc)
{
    /* Note that the key is the implementation independent part of the ffp_frag_desc structure,
     * whereas desc points to an extended structure with implementation specific parts. */
    if (wine_rb_put(shaders, &desc->settings, &desc->entry) == -1)
    {
        ERR("Failed to insert ffp frag shader.\n");
    }
}