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
struct wined3d_color {float r; float g; float b; float a; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 float D3DCOLOR_B_A (int /*<<< orphan*/ ) ; 
 float D3DCOLOR_B_B (int /*<<< orphan*/ ) ; 
 float D3DCOLOR_B_G (int /*<<< orphan*/ ) ; 
 float D3DCOLOR_B_R (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wined3d_color_from_d3dcolor(struct wined3d_color *wined3d_color, DWORD d3d_color)
{
    wined3d_color->r = D3DCOLOR_B_R(d3d_color) / 255.0f;
    wined3d_color->g = D3DCOLOR_B_G(d3d_color) / 255.0f;
    wined3d_color->b = D3DCOLOR_B_B(d3d_color) / 255.0f;
    wined3d_color->a = D3DCOLOR_B_A(d3d_color) / 255.0f;
}