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
typedef  int stb_uint ;

/* Variables and functions */
 int /*<<< orphan*/  stb_out (int) ; 

__attribute__((used)) static void stb_out4(stb_uint v) { stb_out(v >> 24); stb_out(v >> 16);
                                   stb_out(v >> 8 ); stb_out(v);                  }