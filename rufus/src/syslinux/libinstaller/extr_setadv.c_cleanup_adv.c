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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_MAGIC1 ; 
 int /*<<< orphan*/  ADV_MAGIC2 ; 
 int /*<<< orphan*/  ADV_MAGIC3 ; 
 int ADV_SIZE ; 
 scalar_t__ get_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  set_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_adv(unsigned char *advbuf)
{
    int i;
    uint32_t csum;

    /* Make sure both copies agree, and update the checksum */
    set_32((uint32_t *) advbuf, ADV_MAGIC1);

    csum = ADV_MAGIC2;
    for (i = 8; i < ADV_SIZE - 4; i += 4)
	csum -= get_32((uint32_t *) (advbuf + i));

    set_32((uint32_t *) (advbuf + 4), csum);
    set_32((uint32_t *) (advbuf + ADV_SIZE - 4), ADV_MAGIC3);

    memcpy(advbuf + ADV_SIZE, advbuf, ADV_SIZE);
}