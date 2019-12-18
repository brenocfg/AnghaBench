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
typedef  scalar_t__ uint8 ;
struct TYPE_3__ {scalar_t__ sparse; } ;
typedef  TYPE_1__ Codebook ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NO_CODE ; 
 scalar_t__ STB_VORBIS_FAST_HUFFMAN_LENGTH ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int include_in_sort(Codebook *c, uint8 len)
{
   if (c->sparse) { assert(len != NO_CODE); return TRUE; }
   if (len == NO_CODE) return FALSE;
   if (len > STB_VORBIS_FAST_HUFFMAN_LENGTH) return TRUE;
   return FALSE;
}