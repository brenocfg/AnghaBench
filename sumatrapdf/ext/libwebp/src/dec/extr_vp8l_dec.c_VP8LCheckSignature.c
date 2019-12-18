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
typedef  int uint8_t ;

/* Variables and functions */
 size_t VP8L_FRAME_HEADER_SIZE ; 
 int const VP8L_MAGIC_BYTE ; 

int VP8LCheckSignature(const uint8_t* const data, size_t size) {
  return (size >= VP8L_FRAME_HEADER_SIZE &&
          data[0] == VP8L_MAGIC_BYTE &&
          (data[4] >> 5) == 0);  // version
}