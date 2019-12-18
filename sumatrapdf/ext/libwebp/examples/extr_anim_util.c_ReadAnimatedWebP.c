#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_8__ {int canvas_width; int canvas_height; int frame_count; int /*<<< orphan*/  bgcolor; int /*<<< orphan*/  loop_count; } ;
typedef  TYPE_1__ WebPAnimInfo ;
typedef  int /*<<< orphan*/  WebPAnimDecoder ;
typedef  int /*<<< orphan*/  W_CHAR ;
struct TYPE_10__ {int canvas_width; int canvas_height; int /*<<< orphan*/  format; TYPE_2__* frames; int /*<<< orphan*/  bgcolor; int /*<<< orphan*/  loop_count; } ;
struct TYPE_9__ {int duration; scalar_t__ is_key_frame; int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_2__ DecodedFrame ;
typedef  TYPE_3__ AnimatedImage ;

/* Variables and functions */
 int /*<<< orphan*/  ANIM_WEBP ; 
 int /*<<< orphan*/  AllocateFrames (TYPE_3__* const,int) ; 
 int /*<<< orphan*/  CleanupTransparentPixels (int*,int,int) ; 
 int DumpFrame (char const*,char const*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPAnimDecoderDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPAnimDecoderGetInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  WebPAnimDecoderGetNext (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ WebPAnimDecoderHasMoreFrames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPAnimDecoderNew (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int kNumChannels ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int ReadAnimatedWebP(const char filename[],
                            const WebPData* const webp_data,
                            AnimatedImage* const image, int dump_frames,
                            const char dump_folder[]) {
  int ok = 0;
  int dump_ok = 1;
  uint32_t frame_index = 0;
  int prev_frame_timestamp = 0;
  WebPAnimDecoder* dec;
  WebPAnimInfo anim_info;

  memset(image, 0, sizeof(*image));

  dec = WebPAnimDecoderNew(webp_data, NULL);
  if (dec == NULL) {
    WFPRINTF(stderr, "Error parsing image: %s\n", (const W_CHAR*)filename);
    goto End;
  }

  if (!WebPAnimDecoderGetInfo(dec, &anim_info)) {
    fprintf(stderr, "Error getting global info about the animation\n");
    goto End;
  }

  // Animation properties.
  image->canvas_width = anim_info.canvas_width;
  image->canvas_height = anim_info.canvas_height;
  image->loop_count = anim_info.loop_count;
  image->bgcolor = anim_info.bgcolor;

  // Allocate frames.
  if (!AllocateFrames(image, anim_info.frame_count)) return 0;

  // Decode frames.
  while (WebPAnimDecoderHasMoreFrames(dec)) {
    DecodedFrame* curr_frame;
    uint8_t* curr_rgba;
    uint8_t* frame_rgba;
    int timestamp;

    if (!WebPAnimDecoderGetNext(dec, &frame_rgba, &timestamp)) {
      fprintf(stderr, "Error decoding frame #%u\n", frame_index);
      goto End;
    }
    assert(frame_index < anim_info.frame_count);
    curr_frame = &image->frames[frame_index];
    curr_rgba = curr_frame->rgba;
    curr_frame->duration = timestamp - prev_frame_timestamp;
    curr_frame->is_key_frame = 0;  // Unused.
    memcpy(curr_rgba, frame_rgba,
           image->canvas_width * kNumChannels * image->canvas_height);

    // Needed only because we may want to compare with GIF later.
    CleanupTransparentPixels((uint32_t*)curr_rgba,
                             image->canvas_width, image->canvas_height);

    if (dump_frames && dump_ok) {
      dump_ok = DumpFrame(filename, dump_folder, frame_index, curr_rgba,
                          image->canvas_width, image->canvas_height);
      if (!dump_ok) {  // Print error once, but continue decode loop.
        fprintf(stderr, "Error dumping frames to %s\n", dump_folder);
      }
    }

    ++frame_index;
    prev_frame_timestamp = timestamp;
  }
  ok = dump_ok;
  if (ok) image->format = ANIM_WEBP;

 End:
  WebPAnimDecoderDelete(dec);
  return ok;
}