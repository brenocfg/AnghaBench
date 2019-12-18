#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ color_cache_size_; int num_htree_groups_; TYPE_1__* htree_groups_; } ;
typedef  TYPE_2__ VP8LMetadata ;
struct TYPE_7__ {scalar_t__ bits; } ;
struct TYPE_5__ {TYPE_3__** htrees; } ;
typedef  TYPE_3__ HuffmanCode ;

/* Variables and functions */
 size_t ALPHA ; 
 size_t BLUE ; 
 size_t RED ; 

__attribute__((used)) static int Is8bOptimizable(const VP8LMetadata* const hdr) {
  int i;
  if (hdr->color_cache_size_ > 0) return 0;
  // When the Huffman tree contains only one symbol, we can skip the
  // call to ReadSymbol() for red/blue/alpha channels.
  for (i = 0; i < hdr->num_htree_groups_; ++i) {
    HuffmanCode** const htrees = hdr->htree_groups_[i].htrees;
    if (htrees[RED][0].bits > 0) return 0;
    if (htrees[BLUE][0].bits > 0) return 0;
    if (htrees[ALPHA][0].bits > 0) return 0;
  }
  return 1;
}