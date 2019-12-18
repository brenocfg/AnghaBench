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
 int BPF_DEVCG_ACC_MKNOD ; 
 int BPF_DEVCG_ACC_READ ; 
 int BPF_DEVCG_ACC_WRITE ; 
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 

__attribute__((used)) static int bpf_access_type(const char *acc) {
        int r = 0;

        assert(acc);

        for (; *acc; acc++)
                switch(*acc) {
                case 'r':
                        r |= BPF_DEVCG_ACC_READ;
                        break;
                case 'w':
                        r |= BPF_DEVCG_ACC_WRITE;
                        break;
                case 'm':
                        r |= BPF_DEVCG_ACC_MKNOD;
                        break;
                default:
                        return -EINVAL;
                }

        return r;
}