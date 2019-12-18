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
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMP_SEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  cs ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  r10 ; 
 int /*<<< orphan*/  r11 ; 
 int /*<<< orphan*/  r12 ; 
 int /*<<< orphan*/  r13 ; 
 int /*<<< orphan*/  r14 ; 
 int /*<<< orphan*/  r15 ; 
 int /*<<< orphan*/  r8 ; 
 int /*<<< orphan*/  r9 ; 
 int /*<<< orphan*/  rax ; 
 int /*<<< orphan*/  rbp ; 
 int /*<<< orphan*/  rbx ; 
 int /*<<< orphan*/  rcx ; 
 int /*<<< orphan*/  rdi ; 
 int /*<<< orphan*/  rdx ; 
 int /*<<< orphan*/  rflags ; 
 int /*<<< orphan*/  rip ; 
 int /*<<< orphan*/  rsi ; 
 int /*<<< orphan*/  rsp ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  trapno ; 

void
dump_trapframe(struct trapframe *tf)
{
	DUMP_REG(rdi);
	DUMP_REG(rsi);
	DUMP_REG(rdx);
	DUMP_REG(rcx);
	DUMP_REG(r8);
	DUMP_REG(r9);
	DUMP_REG(rax);
	DUMP_REG(rbx);
	DUMP_REG(rbp);
	DUMP_REG(r10);
	DUMP_REG(r11);
	DUMP_REG(r12);
	DUMP_REG(r13);
	DUMP_REG(r14);
	DUMP_REG(r15);
	DUMP_REG(trapno);
	DUMP_REG(addr);
	DUMP_REG(flags);
	DUMP_REG(err);
	DUMP_REG(rip);
	DUMP_REG(rflags);
	DUMP_REG(rsp);
	DUMP_SEG(cs);
	DUMP_SEG(ss);
	DUMP_SEG(fs);
	DUMP_SEG(gs);
	DUMP_SEG(es);
	DUMP_SEG(ds);
}