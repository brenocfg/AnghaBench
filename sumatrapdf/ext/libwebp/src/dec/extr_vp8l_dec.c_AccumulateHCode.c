#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ bits; scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ bits; int value; } ;
typedef  TYPE_1__ HuffmanCode32 ;
typedef  TYPE_2__ HuffmanCode ;

/* Variables and functions */
 scalar_t__ HUFFMAN_TABLE_BITS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int AccumulateHCode(HuffmanCode hcode, int shift,
                           HuffmanCode32* const huff) {
  huff->bits += hcode.bits;
  huff->value |= (uint32_t)hcode.value << shift;
  assert(huff->bits <= HUFFMAN_TABLE_BITS);
  return hcode.bits;
}