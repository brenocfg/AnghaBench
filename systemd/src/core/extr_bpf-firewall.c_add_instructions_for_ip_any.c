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
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  BPFProgram ;

/* Variables and functions */
 struct bpf_insn const BPF_ALU32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_OR ; 
 int /*<<< orphan*/  BPF_REG_8 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bpf_program_add_instructions (int /*<<< orphan*/ *,struct bpf_insn const*,int) ; 

__attribute__((used)) static int add_instructions_for_ip_any(
                BPFProgram *p,
                int verdict) {
        int r;

        assert(p);

        const struct bpf_insn insn[] = {
                BPF_ALU32_IMM(BPF_OR, BPF_REG_8, verdict),
        };

        r = bpf_program_add_instructions(p, insn, 1);
        if (r < 0)
                return r;

        return 0;
}