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
typedef  int /*<<< orphan*/  stbi ;
struct TYPE_2__ {int size; int channel; void* type; } ;
typedef  TYPE_1__ pic_packet_t ;
typedef  int /*<<< orphan*/  packets ;

/* Variables and functions */
 scalar_t__ at_eof (int /*<<< orphan*/ *) ; 
 int get16 (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 void* get8u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_pic_info(stbi *s, int *x, int *y, int *comp)
{
   int act_comp=0,num_packets=0,chained;
   pic_packet_t packets[10];

   skip(s, 92);

   *x = get16(s);
   *y = get16(s);
   if (at_eof(s))  return 0;
   if ( (*x) != 0 && (1 << 28) / (*x) < (*y)) {
       stbi_rewind( s );
       return 0;
   }

   skip(s, 8);

   do {
      pic_packet_t *packet;

      if (num_packets==sizeof(packets)/sizeof(packets[0]))
         return 0;

      packet = &packets[num_packets++];
      chained = get8(s);
      packet->size    = get8u(s);
      packet->type    = get8u(s);
      packet->channel = get8u(s);
      act_comp |= packet->channel;

      if (at_eof(s)) {
          stbi_rewind( s );
          return 0;
      }
      if (packet->size != 8) {
          stbi_rewind( s );
          return 0;
      }
   } while (chained);

   *comp = (act_comp & 0x10 ? 4 : 3);

   return 1;
}