#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double x; double y; } ;
struct TYPE_7__ {double x; double y; } ;
struct TYPE_6__ {double x; double y; } ;
struct TYPE_5__ {double x; double y; } ;
struct cie1931_primaries {TYPE_4__ white; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */
 size_t BLUE ; 
 int /*<<< orphan*/  Float3Multiply (double*,double*,double*) ; 
 int /*<<< orphan*/  Float3x3Inverse (double*) ; 
 size_t GREEN ; 
 size_t RED ; 

__attribute__((used)) static void GetRGB2XYZMatrix(const struct cie1931_primaries *primaries,
                             double out[3 * 3])
{
#define RED   0
#define GREEN 1
#define BLUE  2
    double X[3], Y[3], Z[3], S[3], W[3];
    double W_TO_S[3 * 3];

    X[RED  ] = primaries->red.x / primaries->red.y;
    X[GREEN] = 1;
    X[BLUE ] = (1 - primaries->red.x - primaries->red.y) / primaries->red.y;

    Y[RED  ] = primaries->green.x / primaries->green.y;
    Y[GREEN] = 1;
    Y[BLUE ] = (1 - primaries->green.x - primaries->green.y) / primaries->green.y;

    Z[RED  ] = primaries->blue.x / primaries->blue.y;
    Z[GREEN] = 1;
    Z[BLUE ] = (1 - primaries->blue.x - primaries->blue.y) / primaries->blue.y;

    W_TO_S[0 + 0*3] = X[RED  ];
    W_TO_S[1 + 0*3] = X[GREEN];
    W_TO_S[2 + 0*3] = X[BLUE ];
    W_TO_S[0 + 1*3] = Y[RED  ];
    W_TO_S[1 + 1*3] = Y[GREEN];
    W_TO_S[2 + 1*3] = Y[BLUE ];
    W_TO_S[0 + 2*3] = Z[RED  ];
    W_TO_S[1 + 2*3] = Z[GREEN];
    W_TO_S[2 + 2*3] = Z[BLUE ];

    Float3x3Inverse(W_TO_S);

    W[0] = primaries->white.x / primaries->white.y; /* Xw */
    W[1] = 1;                  /* Yw */
    W[2] = (1 - primaries->white.x - primaries->white.y) / primaries->white.y; /* Yw */

    Float3Multiply(W, W_TO_S, S);

    out[0 + 0*3] = S[RED  ] * X[RED  ];
    out[1 + 0*3] = S[GREEN] * Y[RED  ];
    out[2 + 0*3] = S[BLUE ] * Z[RED  ];
    out[0 + 1*3] = S[RED  ] * X[GREEN];
    out[1 + 1*3] = S[GREEN] * Y[GREEN];
    out[2 + 1*3] = S[BLUE ] * Z[GREEN];
    out[0 + 2*3] = S[RED  ] * X[BLUE ];
    out[1 + 2*3] = S[GREEN] * Y[BLUE ];
    out[2 + 2*3] = S[BLUE ] * Z[BLUE ];
#undef RED
#undef GREEN
#undef BLUE
}