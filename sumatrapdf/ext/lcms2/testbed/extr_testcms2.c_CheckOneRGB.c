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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ IsGoodWord (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
cmsInt32Number CheckOneRGB(cmsHTRANSFORM xform, cmsUInt16Number R, cmsUInt16Number G, cmsUInt16Number B, cmsUInt16Number Ro, cmsUInt16Number Go, cmsUInt16Number Bo)
{
    cmsUInt16Number RGB[3];
    cmsUInt16Number Out[3];

    RGB[0] = R;
    RGB[1] = G;
    RGB[2] = B;

    cmsDoTransform(DbgThread(), xform, RGB, Out, 1);

    return IsGoodWord("R", Ro , Out[0]) &&
           IsGoodWord("G", Go , Out[1]) &&
           IsGoodWord("B", Bo , Out[2]);
}