#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32_t ;
struct pbuf {scalar_t__ tot_len; scalar_t__ len; int /*<<< orphan*/  payload; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* input ) (struct pbuf*,TYPE_1__*) ;} ;
typedef  TYPE_1__* PNETIF ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void const* const) ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_RAW ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,void const* const,scalar_t__ const) ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pbuf*,TYPE_1__*) ; 

void
LibIPInsertPacket(void *ifarg,
                  const void *const data,
                  const u32_t size)
{
    struct pbuf *p;

    ASSERT(ifarg);
    ASSERT(data);
    ASSERT(size > 0);

    p = pbuf_alloc(PBUF_RAW, size, PBUF_RAM);
    if (p)
    {
        ASSERT(p->tot_len == p->len);
        ASSERT(p->len == size);

        RtlCopyMemory(p->payload, data, p->len);

        ((PNETIF)ifarg)->input(p, (PNETIF)ifarg);
    }
}