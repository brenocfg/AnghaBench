#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* img_comp; } ;
typedef  TYPE_2__ jpeg ;
typedef  int /*<<< orphan*/  huffman ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_6__ {int dc_pred; } ;

/* Variables and functions */
 int decode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t* dezigzag ; 
 int e (char*,char*) ; 
 int extend_receive (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (short*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_block(jpeg *j, short data[64], huffman *hdc, huffman *hac, int b)
{
   int diff,dc,k;
   int t = decode(j, hdc);
   if (t < 0) return e("bad huffman code","Corrupt JPEG");

   // 0 all the ac values now so we can do it 32-bits at a time
   memset(data,0,64*sizeof(data[0]));

   diff = t ? extend_receive(j, t) : 0;
   dc = j->img_comp[b].dc_pred + diff;
   j->img_comp[b].dc_pred = dc;
   data[0] = (short) dc;

   // decode AC components, see JPEG spec
   k = 1;
   do {
      int r,s;
      int rs = decode(j, hac);
      if (rs < 0) return e("bad huffman code","Corrupt JPEG");
      s = rs & 15;
      r = rs >> 4;
      if (s == 0) {
         if (rs != 0xf0) break; // end block
         k += 16;
      } else {
         k += r;
         // decode into unzigzag'd location
         data[dezigzag[k++]] = (short) extend_receive(j,s);
      }
   } while (k < 64);
   return 1;
}