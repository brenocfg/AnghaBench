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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ALPHA ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_UNSIGNED_IDENTITY_NV ; 
 int /*<<< orphan*/  GL_UNSIGNED_INVERT_NV ; 
 int WINED3DTA_ALPHAREPLICATE ; 
 int WINED3DTA_COMPLEMENT ; 
 int WINED3DTA_SELECTMASK ; 
 int /*<<< orphan*/  d3dta_to_combiner_input (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_src_and_opr_nvrc(DWORD stage, DWORD arg, BOOL is_alpha, GLenum* input, GLenum* mapping, GLenum *component_usage, INT texture_idx) {
    /* The WINED3DTA_COMPLEMENT flag specifies the complement of the input should
    * be used. */
    if (arg & WINED3DTA_COMPLEMENT) *mapping = GL_UNSIGNED_INVERT_NV;
    else *mapping = GL_UNSIGNED_IDENTITY_NV; /* Clamp all values to positive ranges */

    /* The WINED3DTA_ALPHAREPLICATE flag specifies the alpha component of the input
    * should be used for all input components. */
    if (is_alpha || arg & WINED3DTA_ALPHAREPLICATE) *component_usage = GL_ALPHA;
    else *component_usage = GL_RGB;

    *input = d3dta_to_combiner_input(arg & WINED3DTA_SELECTMASK, stage, texture_idx);
}