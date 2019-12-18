#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int a; int c; scalar_t__ ct; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_mqc_byteout (TYPE_1__*) ; 

__attribute__((used)) static void opj_mqc_renorme(opj_mqc_t *mqc)
{
    do {
        mqc->a <<= 1;
        mqc->c <<= 1;
        mqc->ct--;
        if (mqc->ct == 0) {
            opj_mqc_byteout(mqc);
        }
    } while ((mqc->a & 0x8000) == 0);
}