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
struct instr_info {int dummy; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int D3DSI_COMMENTSIZE_MASK ; 
 int D3DSI_COMMENTSIZE_SHIFT ; 

__attribute__((used)) static int instr_comment(const struct instr_info *info, DWORD **ptr, char *buffer, BOOL ps)
{
    *ptr += 1 + ((**ptr & D3DSI_COMMENTSIZE_MASK) >> D3DSI_COMMENTSIZE_SHIFT);
    return 0;
}