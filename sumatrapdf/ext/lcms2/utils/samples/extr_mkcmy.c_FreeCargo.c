#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hRGB; int /*<<< orphan*/  hLab; int /*<<< orphan*/  RGB2Lab; int /*<<< orphan*/  Lab2RGB; } ;
typedef  TYPE_1__* LPCARGO ;

/* Variables and functions */
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void FreeCargo(LPCARGO Cargo)
{
	cmsDeleteTransform(Cargo ->Lab2RGB);
	cmsDeleteTransform(Cargo ->RGB2Lab);
	cmsCloseProfile(Cargo ->hLab);
	cmsCloseProfile(Cargo ->hRGB);
}