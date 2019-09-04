#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ alloc_buffer_length_in_bytes; scalar_t__ alloc_buffer; } ;
struct TYPE_22__ {int* blocksize; int channels; scalar_t__* floor_types; short** finalY; scalar_t__ valid_bits; scalar_t__ temp_offset; float** channel_buffers; int first_decode; int current_loc; int discard_samples_deferred; int current_loc_valid; scalar_t__ previous_length; scalar_t__ last_seg_which; scalar_t__ end_seg_with_known_loc; int page_flag; int known_loc_for_packet; TYPE_3__ alloc; int /*<<< orphan*/ * codebooks; TYPE_1__* floor_config; TYPE_6__* mapping; } ;
typedef  TYPE_4__ vorb ;
typedef  int uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  really_zero_channel ;
struct TYPE_25__ {int floor1_multiplier; int partitions; int* partition_class_list; int* class_dimensions; int* class_subclasses; int* class_masterbooks; int** subclass_books; int values; int** neighbors; int /*<<< orphan*/ * Xlist; } ;
struct TYPE_24__ {int* submap_floor; int coupling_steps; int submaps; int* submap_residue; TYPE_2__* chan; } ;
struct TYPE_23__ {size_t blockflag; size_t mapping; } ;
struct TYPE_20__ {int mux; size_t magnitude; size_t angle; } ;
struct TYPE_19__ {TYPE_7__ floor1; } ;
typedef  TYPE_5__ Mode ;
typedef  TYPE_6__ Mapping ;
typedef  TYPE_7__ Floor1 ;
typedef  int /*<<< orphan*/  Codebook ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (TYPE_4__*) ; 
 int /*<<< orphan*/  DECODE (int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 scalar_t__ INVALID_BITS ; 
 int PAGEFLAG_last_page ; 
 int STB_VORBIS_MAX_CHANNELS ; 
 int TRUE ; 
 int /*<<< orphan*/  VORBIS_invalid_stream ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  decode_residue (TYPE_4__*,float**,int,int,int,int*) ; 
 int /*<<< orphan*/  do_floor (TYPE_4__*,TYPE_6__*,int,int,float*,short*,int /*<<< orphan*/ *) ; 
 int error (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_packet (TYPE_4__*) ; 
 short get_bits (TYPE_4__*,int) ; 
 int ilog (int) ; 
 int /*<<< orphan*/  inverse_mdct (float*,int,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int predict_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short) ; 

__attribute__((used)) static int vorbis_decode_packet_rest(vorb *f, int *len, Mode *m, int left_start, int left_end, int right_start, int right_end, int *p_left)
{
   Mapping *map;
   int i,j,k,n,n2;
   int zero_channel[256];
   int really_zero_channel[256];

// WINDOWING

   n = f->blocksize[m->blockflag];
   map = &f->mapping[m->mapping];

// FLOORS
   n2 = n >> 1;

   CHECK(f);

   for (i=0; i < f->channels; ++i) {
      int s = map->chan[i].mux, floor;
      zero_channel[i] = FALSE;
      floor = map->submap_floor[s];
      if (f->floor_types[floor] == 0) {
         return error(f, VORBIS_invalid_stream);
      } else {
         Floor1 *g = &f->floor_config[floor].floor1;
         if (get_bits(f, 1)) {
            short *finalY;
            uint8 step2_flag[256];
            static int range_list[4] = { 256, 128, 86, 64 };
            int range = range_list[g->floor1_multiplier-1];
            int offset = 2;
            finalY = f->finalY[i];
            finalY[0] = get_bits(f, ilog(range)-1);
            finalY[1] = get_bits(f, ilog(range)-1);
            for (j=0; j < g->partitions; ++j) {
               int pclass = g->partition_class_list[j];
               int cdim = g->class_dimensions[pclass];
               int cbits = g->class_subclasses[pclass];
               int csub = (1 << cbits)-1;
               int cval = 0;
               if (cbits) {
                  Codebook *c = f->codebooks + g->class_masterbooks[pclass];
                  DECODE(cval,f,c);
               }
               for (k=0; k < cdim; ++k) {
                  int book = g->subclass_books[pclass][cval & csub];
                  cval = cval >> cbits;
                  if (book >= 0) {
                     int temp;
                     Codebook *c = f->codebooks + book;
                     DECODE(temp,f,c);
                     finalY[offset++] = temp;
                  } else
                     finalY[offset++] = 0;
               }
            }
            if (f->valid_bits == INVALID_BITS) goto error; // behavior according to spec
            step2_flag[0] = step2_flag[1] = 1;
            for (j=2; j < g->values; ++j) {
               int low, high, pred, highroom, lowroom, room, val;
               low = g->neighbors[j][0];
               high = g->neighbors[j][1];
               //neighbors(g->Xlist, j, &low, &high);
               pred = predict_point(g->Xlist[j], g->Xlist[low], g->Xlist[high], finalY[low], finalY[high]);
               val = finalY[j];
               highroom = range - pred;
               lowroom = pred;
               if (highroom < lowroom)
                  room = highroom * 2;
               else
                  room = lowroom * 2;
               if (val) {
                  step2_flag[low] = step2_flag[high] = 1;
                  step2_flag[j] = 1;
                  if (val >= room)
                     if (highroom > lowroom)
                        finalY[j] = val - lowroom + pred;
                     else
                        finalY[j] = pred - val + highroom - 1;
                  else
                     if (val & 1)
                        finalY[j] = pred - ((val+1)>>1);
                     else
                        finalY[j] = pred + (val>>1);
               } else {
                  step2_flag[j] = 0;
                  finalY[j] = pred;
               }
            }

#ifdef STB_VORBIS_NO_DEFER_FLOOR
            do_floor(f, map, i, n, f->floor_buffers[i], finalY, step2_flag);
#else
            // defer final floor computation until _after_ residue
            for (j=0; j < g->values; ++j) {
               if (!step2_flag[j])
                  finalY[j] = -1;
            }
#endif
         } else {
           error:
            zero_channel[i] = TRUE;
         }
         // So we just defer everything else to later

         // at this point we've decoded the floor into buffer
      }
   }
   CHECK(f);
   // at this point we've decoded all floors

   if (f->alloc.alloc_buffer)
      assert(f->alloc.alloc_buffer_length_in_bytes == f->temp_offset);

   // re-enable coupled channels if necessary
   memcpy(really_zero_channel, zero_channel, sizeof(really_zero_channel[0]) * f->channels);
   for (i=0; i < map->coupling_steps; ++i)
      if (!zero_channel[map->chan[i].magnitude] || !zero_channel[map->chan[i].angle]) {
         zero_channel[map->chan[i].magnitude] = zero_channel[map->chan[i].angle] = FALSE;
      }

   CHECK(f);
// RESIDUE DECODE
   for (i=0; i < map->submaps; ++i) {
      float *residue_buffers[STB_VORBIS_MAX_CHANNELS];
      int r;
      uint8 do_not_decode[256];
      int ch = 0;
      for (j=0; j < f->channels; ++j) {
         if (map->chan[j].mux == i) {
            if (zero_channel[j]) {
               do_not_decode[ch] = TRUE;
               residue_buffers[ch] = NULL;
            } else {
               do_not_decode[ch] = FALSE;
               residue_buffers[ch] = f->channel_buffers[j];
            }
            ++ch;
         }
      }
      r = map->submap_residue[i];
      decode_residue(f, residue_buffers, ch, n2, r, do_not_decode);
   }

   if (f->alloc.alloc_buffer)
      assert(f->alloc.alloc_buffer_length_in_bytes == f->temp_offset);
   CHECK(f);

// INVERSE COUPLING
   for (i = map->coupling_steps-1; i >= 0; --i) {
      int n2 = n >> 1;
      float *m = f->channel_buffers[map->chan[i].magnitude];
      float *a = f->channel_buffers[map->chan[i].angle    ];
      for (j=0; j < n2; ++j) {
         float a2,m2;
         if (m[j] > 0)
            if (a[j] > 0)
               m2 = m[j], a2 = m[j] - a[j];
            else
               a2 = m[j], m2 = m[j] + a[j];
         else
            if (a[j] > 0)
               m2 = m[j], a2 = m[j] + a[j];
            else
               a2 = m[j], m2 = m[j] - a[j];
         m[j] = m2;
         a[j] = a2;
      }
   }
   CHECK(f);

   // finish decoding the floors
#ifndef STB_VORBIS_NO_DEFER_FLOOR
   for (i=0; i < f->channels; ++i) {
      if (really_zero_channel[i]) {
         memset(f->channel_buffers[i], 0, sizeof(*f->channel_buffers[i]) * n2);
      } else {
         do_floor(f, map, i, n, f->channel_buffers[i], f->finalY[i], NULL);
      }
   }
#else
   for (i=0; i < f->channels; ++i) {
      if (really_zero_channel[i]) {
         memset(f->channel_buffers[i], 0, sizeof(*f->channel_buffers[i]) * n2);
      } else {
         for (j=0; j < n2; ++j)
            f->channel_buffers[i][j] *= f->floor_buffers[i][j];
      }
   }
#endif

// INVERSE MDCT
   CHECK(f);
   for (i=0; i < f->channels; ++i)
      inverse_mdct(f->channel_buffers[i], n, f, m->blockflag);
   CHECK(f);

   // this shouldn't be necessary, unless we exited on an error
   // and want to flush to get to the next packet
   flush_packet(f);

   if (f->first_decode) {
      // assume we start so first non-discarded sample is sample 0
      // this isn't to spec, but spec would require us to read ahead
      // and decode the size of all current frames--could be done,
      // but presumably it's not a commonly used feature
      f->current_loc = -n2; // start of first frame is positioned for discard
      // we might have to discard samples "from" the next frame too,
      // if we're lapping a large block then a small at the start?
      f->discard_samples_deferred = n - right_end;
      f->current_loc_valid = TRUE;
      f->first_decode = FALSE;
   } else if (f->discard_samples_deferred) {
      if (f->discard_samples_deferred >= right_start - left_start) {
         f->discard_samples_deferred -= (right_start - left_start);
         left_start = right_start;
         *p_left = left_start;
      } else {
         left_start += f->discard_samples_deferred;
         *p_left = left_start;
         f->discard_samples_deferred = 0;
      }
   } else if (f->previous_length == 0 && f->current_loc_valid) {
      // we're recovering from a seek... that means we're going to discard
      // the samples from this packet even though we know our position from
      // the last page header, so we need to update the position based on
      // the discarded samples here
      // but wait, the code below is going to add this in itself even
      // on a discard, so we don't need to do it here...
   }

   // check if we have ogg information about the sample # for this packet
   if (f->last_seg_which == f->end_seg_with_known_loc) {
      // if we have a valid current loc, and this is final:
      if (f->current_loc_valid && (f->page_flag & PAGEFLAG_last_page)) {
         uint32 current_end = f->known_loc_for_packet;
         // then let's infer the size of the (probably) short final frame
         if (current_end < f->current_loc + (right_end-left_start)) {
            if (current_end < f->current_loc) {
               // negative truncation, that's impossible!
               *len = 0;
            } else {
               *len = current_end - f->current_loc;
            }
            *len += left_start; // this doesn't seem right, but has no ill effect on my test files
            if (*len > right_end) *len = right_end; // this should never happen
            f->current_loc += *len;
            return TRUE;
         }
      }
      // otherwise, just set our sample loc
      // guess that the ogg granule pos refers to the _middle_ of the
      // last frame?
      // set f->current_loc to the position of left_start
      f->current_loc = f->known_loc_for_packet - (n2-left_start);
      f->current_loc_valid = TRUE;
   }
   if (f->current_loc_valid)
      f->current_loc += (right_start - left_start);

   if (f->alloc.alloc_buffer)
      assert(f->alloc.alloc_buffer_length_in_bytes == f->temp_offset);
   *len = right_end;  // ignore samples after the window goes to 0
   CHECK(f);

   return TRUE;
}