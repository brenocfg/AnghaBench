#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int _11; int _21; int _12; int _31; int _13; int _41; int _14; int _22; int _23; int _24; int _32; int _33; int _34; int _42; int _43; int _44; } ;
typedef  int /*<<< orphan*/  D3DVALUE ;
typedef  TYPE_1__ D3DMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void
multiply_matrix(D3DMATRIX *dest,
                const D3DMATRIX *src1,
                const D3DMATRIX *src2)
{
    D3DMATRIX temp;

    /* Now do the multiplication 'by hand'.
       I know that all this could be optimised, but this will be done later :-) */
    temp._11 = (src1->_11 * src2->_11) + (src1->_21 * src2->_12) + (src1->_31 * src2->_13) + (src1->_41 * src2->_14);
    temp._21 = (src1->_11 * src2->_21) + (src1->_21 * src2->_22) + (src1->_31 * src2->_23) + (src1->_41 * src2->_24);
    temp._31 = (src1->_11 * src2->_31) + (src1->_21 * src2->_32) + (src1->_31 * src2->_33) + (src1->_41 * src2->_34);
    temp._41 = (src1->_11 * src2->_41) + (src1->_21 * src2->_42) + (src1->_31 * src2->_43) + (src1->_41 * src2->_44);

    temp._12 = (src1->_12 * src2->_11) + (src1->_22 * src2->_12) + (src1->_32 * src2->_13) + (src1->_42 * src2->_14);
    temp._22 = (src1->_12 * src2->_21) + (src1->_22 * src2->_22) + (src1->_32 * src2->_23) + (src1->_42 * src2->_24);
    temp._32 = (src1->_12 * src2->_31) + (src1->_22 * src2->_32) + (src1->_32 * src2->_33) + (src1->_42 * src2->_34);
    temp._42 = (src1->_12 * src2->_41) + (src1->_22 * src2->_42) + (src1->_32 * src2->_43) + (src1->_42 * src2->_44);

    temp._13 = (src1->_13 * src2->_11) + (src1->_23 * src2->_12) + (src1->_33 * src2->_13) + (src1->_43 * src2->_14);
    temp._23 = (src1->_13 * src2->_21) + (src1->_23 * src2->_22) + (src1->_33 * src2->_23) + (src1->_43 * src2->_24);
    temp._33 = (src1->_13 * src2->_31) + (src1->_23 * src2->_32) + (src1->_33 * src2->_33) + (src1->_43 * src2->_34);
    temp._43 = (src1->_13 * src2->_41) + (src1->_23 * src2->_42) + (src1->_33 * src2->_43) + (src1->_43 * src2->_44);

    temp._14 = (src1->_14 * src2->_11) + (src1->_24 * src2->_12) + (src1->_34 * src2->_13) + (src1->_44 * src2->_14);
    temp._24 = (src1->_14 * src2->_21) + (src1->_24 * src2->_22) + (src1->_34 * src2->_23) + (src1->_44 * src2->_24);
    temp._34 = (src1->_14 * src2->_31) + (src1->_24 * src2->_32) + (src1->_34 * src2->_33) + (src1->_44 * src2->_34);
    temp._44 = (src1->_14 * src2->_41) + (src1->_24 * src2->_42) + (src1->_34 * src2->_43) + (src1->_44 * src2->_44);

    /* And copy the new matrix in the good storage.. */
    memcpy(dest, &temp, 16 * sizeof(D3DVALUE));
}