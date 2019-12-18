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
typedef  int stb_uint ;
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stb__out ; 
 int /*<<< orphan*/  stb__outfile ; 

__attribute__((used)) static void stb_out_backpatch(size_t id, stb_uint value)
{
   stb_uchar data[4] = { (stb_uchar)(value >> 24), (stb_uchar)(value >> 16), (stb_uchar)(value >> 8), (stb_uchar)(value) };
   if (stb__out) {
      memcpy((void *) id, data, 4);
   } else {
      stb_uint where = ftell(stb__outfile);
      fseek(stb__outfile, (long) id, SEEK_SET);
      fwrite(data, 4, 1, stb__outfile);
      fseek(stb__outfile, where, SEEK_SET);
   }
}