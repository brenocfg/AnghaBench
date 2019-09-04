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
 size_t intel_syntax ; 
 int /*<<< orphan*/  oappend (char*) ; 
 int /*<<< orphan*/  ptr_reg (int,int) ; 

__attribute__((used)) static void
OP_ESreg (int code, int sizeflag)
{
  oappend (&"%es:"[intel_syntax]);
  ptr_reg (code, sizeflag);
}