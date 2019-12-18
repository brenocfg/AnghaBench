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
struct TYPE_3__ {int ri; int bp; int op; int opm; } ;
typedef  TYPE_1__ fz_color_params ;

/* Variables and functions */
 int BP ; 
 int OP ; 
 int OPM ; 
 int RI ; 

__attribute__((used)) static int
fz_pack_color_params(fz_color_params color_params)
{
	int flags = 0;
	flags |= color_params.ri << RI; /* 2 bits */
	flags |= color_params.bp << BP;
	flags |= color_params.op << OP;
	flags |= color_params.opm << OPM;
	return flags;
}