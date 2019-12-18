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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int CHUNK_SIZE_BYTES ; 
 size_t MKFOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  PutLE32 (int /*<<< orphan*/ * const,size_t) ; 
 int RIFF_HEADER_SIZE ; 
 int TAG_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

uint8_t* MuxEmitRiffHeader(uint8_t* const data, size_t size) {
  PutLE32(data + 0, MKFOURCC('R', 'I', 'F', 'F'));
  PutLE32(data + TAG_SIZE, (uint32_t)size - CHUNK_HEADER_SIZE);
  assert(size == (uint32_t)size);
  PutLE32(data + TAG_SIZE + CHUNK_SIZE_BYTES, MKFOURCC('W', 'E', 'B', 'P'));
  return data + RIFF_HEADER_SIZE;
}