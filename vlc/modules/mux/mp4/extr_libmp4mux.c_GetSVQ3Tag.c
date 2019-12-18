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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int GetDWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static bo_t *GetSVQ3Tag(const uint8_t *p_extra, size_t i_extra)
{
    bo_t *smi = box_new("SMI ");
    if(!smi)
        return NULL;

    if (i_extra > 0x4e) {
        const uint8_t *p_end = &p_extra[i_extra];
        const uint8_t *p     = &p_extra[0x46];

        while (p + 8 < p_end) {
            int i_size = GetDWBE(p);
            if (i_size <= 1) /* FIXME handle 1 as long size */
                break;
            if (!strncmp((const char *)&p[4], "SMI ", 4)) {
                bo_add_mem(smi, p_end - p - 8, &p[8]);
                return smi;
            }
            p += i_size;
        }
    }

    /* Create a dummy one in fallback */
    bo_add_fourcc(smi, "SEQH");
    bo_add_32be(smi, 0x5);
    bo_add_32be(smi, 0xe2c0211d);
    bo_add_8(smi, 0xc0);

    return smi;
}