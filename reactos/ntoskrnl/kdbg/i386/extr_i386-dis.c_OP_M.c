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

/* Variables and functions */
 int /*<<< orphan*/  BadOp () ; 
 int /*<<< orphan*/  OP_E (int,int) ; 
 int mod ; 

__attribute__((used)) static void
OP_M (int bytemode, int sizeflag)
{
  if (mod == 3)
    BadOp ();	/* bad lea,lds,les,lfs,lgs,lss modrm */
  else
    OP_E (bytemode, sizeflag);
}