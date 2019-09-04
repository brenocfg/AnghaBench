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
struct wined3d_state {int /*<<< orphan*/ * shader; } ;
typedef  int BOOL ;

/* Variables and functions */
 size_t WINED3D_SHADER_TYPE_PIXEL ; 

__attribute__((used)) static inline BOOL use_ps(const struct wined3d_state *state)
{
    return !!state->shader[WINED3D_SHADER_TYPE_PIXEL];
}