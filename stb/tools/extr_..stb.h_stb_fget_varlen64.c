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
typedef  int stb_uint64 ;
typedef  int stb_uint ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int stb_fgetc (int /*<<< orphan*/ *) ; 

stb_uint64   stb_fget_varlen64(FILE *f)
{
   stb_uint64 z;
   unsigned char d;
   d = stb_fgetc(f);

   if (d >= 0x80) {
      if (d >= 0xc0) {
         if (d >= 0xe0) {
            if (d >= 0xf0) {
               if (d >= 0xf8) {
                  if (d >= 0xfc) {
                     if (d >= 0xfe) {
                        if (d >= 0xff)
                           z = (stb_uint64) stb_fgetc(f) << 56;
                        else
                           z = (stb_uint64) (d - 0xfe) << 56;
                        z |= (stb_uint64) stb_fgetc(f) << 48;
                     } else z = (stb_uint64) (d - 0xfc) << 48;
                     z |= (stb_uint64) stb_fgetc(f) << 40;
                  } else z = (stb_uint64) (d - 0xf8) << 40;
                  z |= (stb_uint64) stb_fgetc(f) << 32;
               } else z = (stb_uint64) (d - 0xf0) << 32;
               z |= (stb_uint) stb_fgetc(f) << 24;
            } else z = (stb_uint) (d - 0xe0) << 24;
            z |= (stb_uint) stb_fgetc(f) << 16;
         } else z = (stb_uint) (d - 0xc0) << 16;
         z |= (stb_uint) stb_fgetc(f) << 8;
      } else z = (stb_uint) (d - 0x80) << 8;
      z |= stb_fgetc(f);
   } else
      z = d;

   return (z & 1) ? ~(z >> 1) : (z >> 1);
}