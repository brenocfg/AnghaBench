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
struct TYPE_3__ {int alloc_buffer_length_in_bytes; int /*<<< orphan*/  alloc_buffer; } ;
typedef  TYPE_1__ stb_vorbis_alloc ;
typedef  int /*<<< orphan*/  stb_vorbis ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (short*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  stb_vorbis_close (int /*<<< orphan*/ *) ; 
 unsigned int stb_vorbis_decode_filename (char*,int*,int*,short**) ; 
 int /*<<< orphan*/ * stb_vorbis_open_filename (char*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int* test_count ; 
 unsigned int* test_spacing ; 
 scalar_t__ try_seeking (int /*<<< orphan*/ *,unsigned int,short*,unsigned int) ; 

int main(int argc, char **argv)
{
   int num_chan, samprate;
   int i, j, test, phase;
   short *output;

   if (argc == 1) {
      fprintf(stderr, "Usage: vorbseek {vorbisfile} [{vorbisfile]*]\n");
      fprintf(stderr, "Tests various seek offsets to make sure they're sample exact.\n");
      return 0;
   }

   #if 0
   {
      // check that outofmem occurs correctly
      stb_vorbis_alloc va;
      va.alloc_buffer = malloc(1024*1024);
      for (i=0; i < 1024*1024; i += 10) {
         int error=0;
         stb_vorbis *v;
         va.alloc_buffer_length_in_bytes = i;
         v = stb_vorbis_open_filename(argv[1], &error, &va);
         if (v != NULL)
            break;
         printf("Error %d at %d\n", error, i);
      }
   }
   #endif

   for (j=1; j < argc; ++j) {
      unsigned int successes=0, attempts = 0;
      unsigned int num_samples = stb_vorbis_decode_filename(argv[j], &num_chan, &samprate, &output);

      break;

      if (num_samples == 0xffffffff) {
         fprintf(stderr, "Error: couldn't open file or not vorbis file: %s\n", argv[j]);
         goto fail;
      }

      if (num_chan != 2) {
         fprintf(stderr, "vorbseek testing only works with files with 2 channels, %s has %d\n", argv[j], num_chan);
         goto fail;
      }

      for (test=0; test < 5; ++test) {
         int error;
         stb_vorbis *v = stb_vorbis_open_filename(argv[j], &error, NULL);
         if (v == NULL) {
            fprintf(stderr, "Couldn't re-open %s for test #%d\n", argv[j], test);
            goto fail;
         }
         for (phase=0; phase < 3; ++phase) {
            unsigned int base = phase == 0 ? 0 : phase == 1 ? num_samples - test_count[test]*test_spacing[test] : num_samples/3;
            for (i=0; i < test_count[test]; ++i) {
               unsigned int pos = base + i*test_spacing[test];
               if (pos > num_samples) // this also catches underflows
                  continue;
               successes += try_seeking(v, pos, output, num_samples);
               attempts += 1;
            }
         }
         stb_vorbis_close(v);
      }
      printf("%d of %d seeks failed in %s (%d samples)\n", attempts-successes, attempts, argv[j], num_samples);
      free(output);
   }
   return 0;
  fail:
   return 1;
}