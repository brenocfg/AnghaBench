#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char** blockdata; unsigned char** data; unsigned char** light; unsigned char** skylight; unsigned char* pointer_to_free; } ;
typedef  TYPE_1__ fast_chunk ;

/* Variables and functions */
 unsigned char STBVOX_MAKE_LIGHTING_EXT (unsigned char,unsigned char) ; 
 unsigned char* effective_blocktype ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int* remap ; 
 unsigned char** remap_data ; 
 unsigned char* rotate_data ; 

void convert_fastchunk_inplace(fast_chunk *fc)
{
   int i;
   int num_blocks=0, step=0;
   unsigned char rot[4096];
   #ifndef IN_PLACE
   unsigned char *storage;
   #endif

   memset(rot, 0, 4096);

   for (i=0; i < 16; ++i)
      num_blocks += fc->blockdata[i] != NULL;

   #ifndef IN_PLACE
   storage = malloc(16*16*16*2 * num_blocks);
   #endif

   for (i=0; i < 16; ++i) {
      if (fc->blockdata[i]) {
         int o=0;
         unsigned char *bd,*dd,*lt,*sky;
         unsigned char *out, *outb;

         // this ordering allows us to determine which data we can safely overwrite for in-place processing
         bd = fc->blockdata[i];
         dd = fc->data[i];
         lt = fc->light[i];
         sky = fc->skylight[i];

         #ifdef IN_PLACE
         out = bd;
         #else
         out = storage + 16*16*16*2*step;
         #endif

         // bd is written in place, but also reads from dd
         for (o=0; o < 16*16*16/2; o += 1) {
            unsigned char v1,v2;
            unsigned char d = dd[o];
            v1 = bd[o*2+0];
            v2 = bd[o*2+1];

            if (remap[v1])
            {
               //unsigned char d = bd[o] & 15;
               v1 = remap_data[remap[v1]][d&15];
               rot[o*2+0] = rotate_data[d&3];
            } else
               v1 = effective_blocktype[v1];

            if (remap[v2])
            {
               //unsigned char d = bd[o] >> 4;
               v2 = remap_data[remap[v2]][d>>4];
               rot[o*2+1] = rotate_data[(d>>4)&3];
            } else
               v2 = effective_blocktype[v2];

            out[o*2+0] = v1;
            out[o*2+1] = v2;
         }

         // this reads from lt & sky
         #ifndef IN_PLACE
         outb = out + 16*16*16;
         ++step;
         #endif

         // MC used to write in this order and it makes it possible to compute in-place
         if (dd < sky && sky < lt) {
            // @TODO go this path always if !IN_PLACE
            #ifdef IN_PLACE
            outb = dd;
            #endif

            for (o=0; o < 16*16*16/2; ++o) {
               int bright;
               bright = (lt[o]&15)*12 + 15 + (sky[o]&15)*16;
               if (bright > 255) bright = 255;
               if (bright <  32) bright =  32;
               outb[o*2+0] = STBVOX_MAKE_LIGHTING_EXT((unsigned char) bright, (rot[o*2+0]&3));

               bright = (lt[o]>>4)*12 + 15 + (sky[o]>>4)*16;
               if (bright > 255) bright = 255;
               if (bright <  32) bright =  32;
               outb[o*2+1] = STBVOX_MAKE_LIGHTING_EXT((unsigned char) bright, (rot[o*2+1]&3));
            }
         } else {
            // @TODO: if blocktype is in between others, this breaks; need to find which side has two pointers, and use that
            // overwrite rot[] array, then copy out
            #ifdef IN_PLACE
            outb = (dd < sky) ? dd : sky;
            if (lt < outb) lt = outb;
            #endif

            for (o=0; o < 16*16*16/2; ++o) {
               int bright;
               bright = (lt[o]&15)*12 + 15 + (sky[o]&15)*16;
               if (bright > 255) bright = 255;
               if (bright <  32) bright =  32;
               rot[o*2+0] = STBVOX_MAKE_LIGHTING_EXT((unsigned char) bright, (rot[o*2+0]&3));

               bright = (lt[o]>>4)*12 + 15 + (sky[o]>>4)*16;
               if (bright > 255) bright = 255;
               if (bright <  32) bright =  32;
               rot[o*2+1] = STBVOX_MAKE_LIGHTING_EXT((unsigned char) bright, (rot[o*2+1]&3));
            }

            memcpy(outb, rot, 4096);
            fc->data[i] = outb;
         }

         #ifndef IN_PLACE
         fc->blockdata[i] = out;
         fc->data[i] = outb;
         #endif
      }
   }

   #ifndef IN_PLACE
   free(fc->pointer_to_free);
   fc->pointer_to_free = storage;
   #endif
}