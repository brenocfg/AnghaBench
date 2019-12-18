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
struct TYPE_7__ {int bytes_in_seg; int packet_bytes; int next_seg; int segment_count; scalar_t__ valid_bits; TYPE_1__* mode_config; scalar_t__ mode_count; } ;
typedef  TYPE_2__ vorb ;
struct TYPE_6__ {scalar_t__ blockflag; } ;

/* Variables and functions */
 int ilog (scalar_t__) ; 
 int /*<<< orphan*/  skip (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vorbis_decode_initial (TYPE_2__*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int peek_decode_initial(vorb *f, int *p_left_start, int *p_left_end, int *p_right_start, int *p_right_end, int *mode)
{
   int bits_read, bytes_read;

   if (!vorbis_decode_initial(f, p_left_start, p_left_end, p_right_start, p_right_end, mode))
      return 0;

   // either 1 or 2 bytes were read, figure out which so we can rewind
   bits_read = 1 + ilog(f->mode_count-1);
   if (f->mode_config[*mode].blockflag)
      bits_read += 2;
   bytes_read = (bits_read + 7) / 8;

   f->bytes_in_seg += bytes_read;
   f->packet_bytes -= bytes_read;
   skip(f, -bytes_read);
   if (f->next_seg == -1)
      f->next_seg = f->segment_count - 1;
   else
      f->next_seg--;
   f->valid_bits = 0;

   return 1;
}