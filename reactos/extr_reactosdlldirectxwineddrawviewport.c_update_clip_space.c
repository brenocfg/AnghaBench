#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_vec3 {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wined3d_matrix {int dummy; } ;
struct TYPE_4__ {float member_1; float member_2; float member_3; float member_4; float member_6; float member_7; float member_8; float member_9; float member_11; float member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_0; } ;
struct d3d_device {TYPE_1__ legacy_clipspace; int /*<<< orphan*/  wined3d_device; int /*<<< orphan*/  legacy_projection; } ;
typedef  TYPE_1__ D3DMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_TS_PROJECTION ; 
 int /*<<< orphan*/  multiply_matrix (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_device_set_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wined3d_matrix*) ; 

__attribute__((used)) static void update_clip_space(struct d3d_device *device,
        struct wined3d_vec3 *scale, struct wined3d_vec3 *offset)
{
    D3DMATRIX clip_space =
    {
        scale->x,  0.0f,      0.0f,      0.0f,
        0.0f,      scale->y,  0.0f,      0.0f,
        0.0f,      0.0f,      scale->z,  0.0f,
        offset->x, offset->y, offset->z, 1.0f,
    };
    D3DMATRIX projection;

    multiply_matrix(&projection, &clip_space, &device->legacy_projection);
    wined3d_device_set_transform(device->wined3d_device,
            WINED3D_TS_PROJECTION, (struct wined3d_matrix *)&projection);
    device->legacy_clipspace = clip_space;
}