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
typedef  int uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int MAX_CANVAS_SIZE ; 
 int MAX_IMAGE_AREA ; 
 size_t MKFOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  PutLE24 (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  PutLE32 (int /*<<< orphan*/ * const,size_t) ; 
 int TAG_SIZE ; 
 size_t VP8X_CHUNK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint8_t* EmitVP8XChunk(uint8_t* const dst, int width,
                              int height, uint32_t flags) {
  const size_t vp8x_size = CHUNK_HEADER_SIZE + VP8X_CHUNK_SIZE;
  assert(width >= 1 && height >= 1);
  assert(width <= MAX_CANVAS_SIZE && height <= MAX_CANVAS_SIZE);
  assert(width * (uint64_t)height < MAX_IMAGE_AREA);
  PutLE32(dst, MKFOURCC('V', 'P', '8', 'X'));
  PutLE32(dst + TAG_SIZE, VP8X_CHUNK_SIZE);
  PutLE32(dst + CHUNK_HEADER_SIZE, flags);
  PutLE24(dst + CHUNK_HEADER_SIZE + 4, width - 1);
  PutLE24(dst + CHUNK_HEADER_SIZE + 7, height - 1);
  return dst + vp8x_size;
}