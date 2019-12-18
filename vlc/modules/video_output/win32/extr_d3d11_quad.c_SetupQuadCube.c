#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ind ;
struct TYPE_10__ {float x; float y; } ;
struct TYPE_9__ {float x; float y; float z; } ;
struct TYPE_11__ {TYPE_2__ texture; TYPE_1__ position; } ;
typedef  TYPE_3__ d3d_vertex_t ;
struct TYPE_12__ {float i_width; float i_height; } ;
typedef  TYPE_4__ d3d_quad_t ;
typedef  int WORD ;
struct TYPE_13__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_5__ RECT ;

/* Variables and functions */
 int ARRAY_SIZE (float const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void SetupQuadCube(d3d_vertex_t *dst_data, const RECT *output,
                          const d3d_quad_t *quad, WORD *triangle_pos)
{
    static const float coord[] = {
        -1.0,    1.0,    -1.0f, // front
        -1.0,    -1.0,   -1.0f,
        1.0,     1.0,    -1.0f,
        1.0,     -1.0,   -1.0f,

        -1.0,    1.0,    1.0f, // back
        -1.0,    -1.0,   1.0f,
        1.0,     1.0,    1.0f,
        1.0,     -1.0,   1.0f,

        -1.0,    1.0,    -1.0f, // left
        -1.0,    -1.0,   -1.0f,
        -1.0,     1.0,    1.0f,
        -1.0,     -1.0,   1.0f,

        1.0f,    1.0,    -1.0f, // right
        1.0f,   -1.0,    -1.0f,
        1.0f,   1.0,     1.0f,
        1.0f,   -1.0,    1.0f,

        -1.0,    -1.0,    1.0f, // bottom
        -1.0,    -1.0,   -1.0f,
        1.0,     -1.0,    1.0f,
        1.0,     -1.0,   -1.0f,

        -1.0,    1.0,    1.0f, // top
        -1.0,    1.0,   -1.0f,
        1.0,     1.0,    1.0f,
        1.0,     1.0,   -1.0f,
    };

    const float scaleX = (float)(output->right - output->left) / quad->i_width;
    const float scaleY = (float)(output->bottom - output->top) / quad->i_height;

    const float col[] = {0.f, scaleX / 3, scaleX * 2 / 3, scaleX};
    const float row[] = {0.f, scaleY / 2, scaleY};

    const float tex[] = {
        col[1], row[1], // front
        col[1], row[2],
        col[2], row[1],
        col[2], row[2],

        col[3], row[1], // back
        col[3], row[2],
        col[2], row[1],
        col[2], row[2],

        col[2], row[0], // left
        col[2], row[1],
        col[1], row[0],
        col[1], row[1],

        col[0], row[0], // right
        col[0], row[1],
        col[1], row[0],
        col[1], row[1],

        col[0], row[2], // bottom
        col[0], row[1],
        col[1], row[2],
        col[1], row[1],

        col[2], row[0], // top
        col[2], row[1],
        col[3], row[0],
        col[3], row[1],
    };

    const unsigned i_nbVertices = ARRAY_SIZE(coord) / 3;

    for (unsigned v = 0; v < i_nbVertices; ++v)
    {
        dst_data[v].position.x = coord[3 * v];
        dst_data[v].position.y = coord[3 * v + 1];
        dst_data[v].position.z = coord[3 * v + 2];

        dst_data[v].texture.x = tex[2 * v];
        dst_data[v].texture.y = tex[2 * v + 1];
    }

    const WORD ind[] = {
        2, 1, 0,       3, 1, 2, // front
        4, 7, 6,       5, 7, 4, // back
        8, 11, 10,     9, 11, 8, // left
        14, 13, 12,    15, 13, 14, // right
        16, 19, 18,    17, 19, 16, // bottom
        22, 21, 20,    23, 21, 22, // top
    };

    memcpy(triangle_pos, ind, sizeof(ind));
}