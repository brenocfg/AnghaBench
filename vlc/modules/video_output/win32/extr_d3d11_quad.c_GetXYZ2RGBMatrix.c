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
struct cie1931_primaries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Float3x3Inverse (double*) ; 
 int /*<<< orphan*/  GetRGB2XYZMatrix (struct cie1931_primaries const*,double*) ; 

__attribute__((used)) static void GetXYZ2RGBMatrix(const struct cie1931_primaries *primaries,
                             double out[3 * 3])
{
    GetRGB2XYZMatrix(primaries, out);
    Float3x3Inverse(out);
}