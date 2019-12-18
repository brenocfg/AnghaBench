#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float x; float y; } ;
struct TYPE_7__ {float x; float y; float z; } ;
struct TYPE_9__ {TYPE_2__ texture; TYPE_1__ position; } ;
typedef  TYPE_3__ d3d_vertex_t ;
struct TYPE_10__ {float i_width; float i_height; } ;
typedef  TYPE_4__ d3d_quad_t ;
typedef  unsigned int WORD ;
typedef  int /*<<< orphan*/  RECT ;

/* Variables and functions */
 scalar_t__ M_PI ; 
 scalar_t__ RECTHeight (int /*<<< orphan*/  const) ; 
 scalar_t__ RECTWidth (int /*<<< orphan*/  const) ; 
 float SPHERE_RADIUS ; 
 unsigned int nbLatBands ; 
 unsigned int nbLonBands ; 
 int /*<<< orphan*/  sincosf (float,float*,float*) ; 

__attribute__((used)) static void SetupQuadSphere(d3d_vertex_t *dst_data, const RECT *output,
                            const d3d_quad_t *quad, WORD *triangle_pos)
{
    const float scaleX = (float)(RECTWidth(*output))  / quad->i_width;
    const float scaleY = (float)(RECTHeight(*output)) / quad->i_height;
    for (unsigned lat = 0; lat <= nbLatBands; lat++) {
        float theta = lat * (float) M_PI / nbLatBands;
        float sinTheta, cosTheta;

        sincosf(theta, &sinTheta, &cosTheta);

        for (unsigned lon = 0; lon <= nbLonBands; lon++) {
            float phi = lon * 2 * (float) M_PI / nbLonBands;
            float sinPhi, cosPhi;

            sincosf(phi, &sinPhi, &cosPhi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            unsigned off1 = lat * (nbLonBands + 1) + lon;
            dst_data[off1].position.x = SPHERE_RADIUS * x;
            dst_data[off1].position.y = SPHERE_RADIUS * y;
            dst_data[off1].position.z = SPHERE_RADIUS * z;

            dst_data[off1].texture.x = scaleX * lon / (float) nbLonBands; // 0(left) to 1(right)
            dst_data[off1].texture.y = scaleY * lat / (float) nbLatBands; // 0(top) to 1 (bottom)
        }
    }

    for (unsigned lat = 0; lat < nbLatBands; lat++) {
        for (unsigned lon = 0; lon < nbLonBands; lon++) {
            unsigned first = (lat * (nbLonBands + 1)) + lon;
            unsigned second = first + nbLonBands + 1;

            unsigned off = (lat * nbLatBands + lon) * 3 * 2;

            triangle_pos[off] = first;
            triangle_pos[off + 1] = first + 1;
            triangle_pos[off + 2] = second;

            triangle_pos[off + 3] = second;
            triangle_pos[off + 4] = first + 1;
            triangle_pos[off + 5] = second + 1;
        }
    }
}