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
typedef  int uint16_t ;
typedef  int MSize ;
typedef  int /*<<< orphan*/  LexState ;
typedef  int /*<<< orphan*/  GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  bcread_block (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ bcread_swap (int /*<<< orphan*/ *) ; 
 int* proto_uv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcread_uv(LexState *ls, GCproto *pt, MSize sizeuv)
{
  if (sizeuv) {
    uint16_t *uv = proto_uv(pt);
    bcread_block(ls, uv, sizeuv*2);
    /* Swap upvalue refs if the endianess differs. */
    if (bcread_swap(ls)) {
      MSize i;
      for (i = 0; i < sizeuv; i++)
	uv[i] = (uint16_t)((uv[i] >> 8)|(uv[i] << 8));
    }
  }
}