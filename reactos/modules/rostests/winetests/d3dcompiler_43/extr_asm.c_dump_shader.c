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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ D3DSIO_END ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void dump_shader(DWORD *shader) {
    unsigned int i = 0, j = 0;
    do {
        trace("0x%08x ", shader[i]);
        j++;
        i++;
        if(j == 6) trace("\n");
    } while(shader[i - 1] != D3DSIO_END);
    if(j != 6) trace("\n");
}