#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  real ;
struct TYPE_5__ {int (* synth ) (int /*<<< orphan*/ *,int,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 
 int stub2 (int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 

__attribute__((used)) static int synth_stereo_wrap(real *bandPtr_l, real *bandPtr_r, mpg123_handle *fr)
{
	int clip;
	clip  = (fr->synth)(bandPtr_l, 0, fr, 0);
	clip += (fr->synth)(bandPtr_r, 1, fr, 1);
	return clip;
}