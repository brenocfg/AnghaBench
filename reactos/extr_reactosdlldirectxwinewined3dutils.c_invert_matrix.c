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
struct wined3d_matrix {float _11; float _12; float _13; float _14; float _21; float _22; float _23; float _24; float _31; float _32; float _33; float _34; float _41; float _42; float _43; float _44; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ fabsf (float) ; 
 int /*<<< orphan*/  swap_rows (float**,float**) ; 

BOOL invert_matrix(struct wined3d_matrix *out, const struct wined3d_matrix *m)
{
    float wtmp[4][8];
    float m0, m1, m2, m3, s;
    float *r0, *r1, *r2, *r3;

    r0 = wtmp[0];
    r1 = wtmp[1];
    r2 = wtmp[2];
    r3 = wtmp[3];

    r0[0] = m->_11;
    r0[1] = m->_12;
    r0[2] = m->_13;
    r0[3] = m->_14;
    r0[4] = 1.0f;
    r0[5] = r0[6] = r0[7] = 0.0f;

    r1[0] = m->_21;
    r1[1] = m->_22;
    r1[2] = m->_23;
    r1[3] = m->_24;
    r1[5] = 1.0f;
    r1[4] = r1[6] = r1[7] = 0.0f;

    r2[0] = m->_31;
    r2[1] = m->_32;
    r2[2] = m->_33;
    r2[3] = m->_34;
    r2[6] = 1.0f;
    r2[4] = r2[5] = r2[7] = 0.0f;

    r3[0] = m->_41;
    r3[1] = m->_42;
    r3[2] = m->_43;
    r3[3] = m->_44;
    r3[7] = 1.0f;
    r3[4] = r3[5] = r3[6] = 0.0f;

    /* Choose pivot - or die. */
    if (fabsf(r3[0]) > fabsf(r2[0]))
        swap_rows(&r3, &r2);
    if (fabsf(r2[0]) > fabsf(r1[0]))
        swap_rows(&r2, &r1);
    if (fabsf(r1[0]) > fabsf(r0[0]))
        swap_rows(&r1, &r0);
    if (r0[0] == 0.0f)
        return FALSE;

    /* Eliminate first variable. */
    m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
    s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
    s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
    s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0f)
    {
        r1[4] -= m1 * s;
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r0[5];
    if (s != 0.0f)
    {
        r1[5] -= m1 * s;
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r0[6];
    if (s != 0.0f)
    {
        r1[6] -= m1 * s;
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r0[7];
    if (s != 0.0f)
    {
        r1[7] -= m1 * s;
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }

    /* Choose pivot - or die. */
    if (fabsf(r3[1]) > fabsf(r2[1]))
        swap_rows(&r3, &r2);
    if (fabsf(r2[1]) > fabsf(r1[1]))
        swap_rows(&r2, &r1);
    if (r1[1] == 0.0f)
        return FALSE;

    /* Eliminate second variable. */
    m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
    r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
    s = r1[4];
    if (s != 0.0f)
    {
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r1[5];
    if (s != 0.0f)
    {
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r1[6];
    if (s != 0.0f)
    {
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r1[7];
    if (s != 0.0f)
    {
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }

    /* Choose pivot - or die. */
    if (fabsf(r3[2]) > fabsf(r2[2]))
        swap_rows(&r3, &r2);
    if (r2[2] == 0.0f)
        return FALSE;

    /* Eliminate third variable. */
    m3 = r3[2] / r2[2];
    r3[3] -= m3 * r2[3];
    r3[4] -= m3 * r2[4];
    r3[5] -= m3 * r2[5];
    r3[6] -= m3 * r2[6];
    r3[7] -= m3 * r2[7];

    /* Last check. */
    if (r3[3] == 0.0f)
        return FALSE;

    /* Back substitute row 3. */
    s = 1.0f / r3[3];
    r3[4] *= s;
    r3[5] *= s;
    r3[6] *= s;
    r3[7] *= s;

    /* Back substitute row 2. */
    m2 = r2[3];
    s = 1.0f / r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2);
    r2[5] = s * (r2[5] - r3[5] * m2);
    r2[6] = s * (r2[6] - r3[6] * m2);
    r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1;
    r1[5] -= r3[5] * m1;
    r1[6] -= r3[6] * m1;
    r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0;
    r0[5] -= r3[5] * m0;
    r0[6] -= r3[6] * m0;
    r0[7] -= r3[7] * m0;

    /* Back substitute row 1. */
    m1 = r1[2];
    s = 1.0f / r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1);
    r1[5] = s * (r1[5] - r2[5] * m1);
    r1[6] = s * (r1[6] - r2[6] * m1);
    r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0;
    r0[5] -= r2[5] * m0;
    r0[6] -= r2[6] * m0;
    r0[7] -= r2[7] * m0;

    /* Back substitute row 0. */
    m0 = r0[1];
    s = 1.0f / r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0);
    r0[5] = s * (r0[5] - r1[5] * m0);
    r0[6] = s * (r0[6] - r1[6] * m0);
    r0[7] = s * (r0[7] - r1[7] * m0);

    out->_11 = r0[4];
    out->_12 = r0[5];
    out->_13 = r0[6];
    out->_14 = r0[7];
    out->_21 = r1[4];
    out->_22 = r1[5];
    out->_23 = r1[6];
    out->_24 = r1[7];
    out->_31 = r2[4];
    out->_32 = r2[5];
    out->_33 = r2[6];
    out->_34 = r2[7];
    out->_41 = r3[4];
    out->_42 = r3[5];
    out->_43 = r3[6];
    out->_44 = r3[7];

    return TRUE;
}