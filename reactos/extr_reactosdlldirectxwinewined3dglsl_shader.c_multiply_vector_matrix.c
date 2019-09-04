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
struct wined3d_vec4 {int x; int y; int z; int w; } ;
struct wined3d_matrix {int _11; int _21; int _31; int _41; int _12; int _22; int _32; int _42; int _13; int _23; int _33; int _43; int _14; int _24; int _34; int _44; } ;

/* Variables and functions */

__attribute__((used)) static void multiply_vector_matrix(struct wined3d_vec4 *dest, const struct wined3d_vec4 *src1,
        const struct wined3d_matrix *src2)
{
    struct wined3d_vec4 temp;

    temp.x = (src1->x * src2->_11) + (src1->y * src2->_21) + (src1->z * src2->_31) + (src1->w * src2->_41);
    temp.y = (src1->x * src2->_12) + (src1->y * src2->_22) + (src1->z * src2->_32) + (src1->w * src2->_42);
    temp.z = (src1->x * src2->_13) + (src1->y * src2->_23) + (src1->z * src2->_33) + (src1->w * src2->_43);
    temp.w = (src1->x * src2->_14) + (src1->y * src2->_24) + (src1->z * src2->_34) + (src1->w * src2->_44);

    *dest = temp;
}