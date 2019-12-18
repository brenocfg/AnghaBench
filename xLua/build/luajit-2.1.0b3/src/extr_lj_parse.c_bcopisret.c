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
typedef  int BCOp ;

/* Variables and functions */
#define  BC_CALLMT 133 
#define  BC_CALLT 132 
#define  BC_RET 131 
#define  BC_RET0 130 
#define  BC_RET1 129 
#define  BC_RETM 128 

__attribute__((used)) static int bcopisret(BCOp op)
{
  switch (op) {
  case BC_CALLMT: case BC_CALLT:
  case BC_RETM: case BC_RET: case BC_RET0: case BC_RET1:
    return 1;
  default:
    return 0;
  }
}