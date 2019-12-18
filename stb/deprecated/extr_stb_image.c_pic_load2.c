#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int stbi_uc ;
typedef  int stbi__uint8 ;
typedef  int /*<<< orphan*/  stbi ;
struct TYPE_2__ {int size; int type; int channel; } ;
typedef  TYPE_1__ pic_packet_t ;
typedef  int /*<<< orphan*/  packets ;

/* Variables and functions */
 scalar_t__ at_eof (int /*<<< orphan*/ *) ; 
 int* epuc (char*,char*) ; 
 int get16 (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 void* get8u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pic_copyval (int,int*,int*) ; 
 int /*<<< orphan*/  pic_readval (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static stbi_uc *pic_load2(stbi *s,int width,int height,int *comp, stbi_uc *result)
{
   int act_comp=0,num_packets=0,y,chained;
   pic_packet_t packets[10];

   // this will (should...) cater for even some bizarre stuff like having data
    // for the same channel in multiple packets.
   do {
      pic_packet_t *packet;

      if (num_packets==sizeof(packets)/sizeof(packets[0]))
         return epuc("bad format","too many packets");

      packet = &packets[num_packets++];

      chained = get8(s);
      packet->size    = get8u(s);
      packet->type    = get8u(s);
      packet->channel = get8u(s);

      act_comp |= packet->channel;

      if (at_eof(s))          return epuc("bad file","file too short (reading packets)");
      if (packet->size != 8)  return epuc("bad format","packet isn't 8bpp");
   } while (chained);

   *comp = (act_comp & 0x10 ? 4 : 3); // has alpha channel?

   for(y=0; y<height; ++y) {
      int packet_idx;

      for(packet_idx=0; packet_idx < num_packets; ++packet_idx) {
         pic_packet_t *packet = &packets[packet_idx];
         stbi_uc *dest = result+y*width*4;

         switch (packet->type) {
            default:
               return epuc("bad format","packet has bad compression type");

            case 0: {//uncompressed
               int x;

               for(x=0;x<width;++x, dest+=4)
                  if (!pic_readval(s,packet->channel,dest))
                     return 0;
               break;
            }

            case 1://Pure RLE
               {
                  int left=width, i;

                  while (left>0) {
                     stbi_uc count,value[4];

                     count=get8u(s);
                     if (at_eof(s))   return epuc("bad file","file too short (pure read count)");

                     if (count > left)
                        count = (stbi__uint8) left;

                     if (!pic_readval(s,packet->channel,value))  return 0;

                     for(i=0; i<count; ++i,dest+=4)
                        pic_copyval(packet->channel,dest,value);
                     left -= count;
                  }
               }
               break;

            case 2: {//Mixed RLE
               int left=width;
               while (left>0) {
                  int count = get8(s), i;
                  if (at_eof(s))  return epuc("bad file","file too short (mixed read count)");

                  if (count >= 128) { // Repeated
                     stbi_uc value[4];
                     int i;

                     if (count==128)
                        count = get16(s);
                     else
                        count -= 127;
                     if (count > left)
                        return epuc("bad file","scanline overrun");

                     if (!pic_readval(s,packet->channel,value))
                        return 0;

                     for(i=0;i<count;++i, dest += 4)
                        pic_copyval(packet->channel,dest,value);
                  } else { // Raw
                     ++count;
                     if (count>left) return epuc("bad file","scanline overrun");

                     for(i=0;i<count;++i, dest+=4)
                        if (!pic_readval(s,packet->channel,dest))
                           return 0;
                  }
                  left-=count;
               }
               break;
            }
         }
      }
   }

   return result;
}