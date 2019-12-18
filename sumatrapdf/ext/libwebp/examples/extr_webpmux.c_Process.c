#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {scalar_t__ bytes; } ;
struct TYPE_18__ {int duration; TYPE_4__ bitstream; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_19__ {int member_0; int loop_count; int /*<<< orphan*/  bgcolor; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_3__ WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  TYPE_4__ WebPData ;
struct TYPE_21__ {int action_type_; size_t type_; int arg_count_; int /*<<< orphan*/  input_; int /*<<< orphan*/  output_; TYPE_1__* args_; } ;
struct TYPE_17__ {int /*<<< orphan*/  params_; int /*<<< orphan*/  filename_; int /*<<< orphan*/  subtype_; } ;
typedef  TYPE_5__ Config ;

/* Variables and functions */
#define  ACTION_DURATION 139 
#define  ACTION_GET 138 
#define  ACTION_INFO 137 
#define  ACTION_SET 136 
#define  ACTION_STRIP 135 
 int CreateMux (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DisplayInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DuplicateMuxHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_GOTO1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_GOTO2 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_GOTO3 (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Err2 ; 
 int /*<<< orphan*/  Err3 ; 
 int ErrorString (int /*<<< orphan*/ ) ; 
 int ExUtilGetInt (int /*<<< orphan*/ ,int,int*) ; 
 int ExUtilGetInts (int /*<<< orphan*/ ,int,int,int*) ; 
 int ExUtilReadFileToWebPData (int /*<<< orphan*/ ,TYPE_4__*) ; 
#define  FEATURE_ANMF 134 
#define  FEATURE_EXIF 133 
#define  FEATURE_ICCP 132 
#define  FEATURE_XMP 131 
 int GetFrame (int /*<<< orphan*/ *,TYPE_5__ const*) ; 
 int ParseBgcolorArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ParseFrameArgs (int /*<<< orphan*/ ,TYPE_2__*) ; 
#define  SUBTYPE_ANMF 130 
#define  SUBTYPE_BGCOLOR 129 
#define  SUBTYPE_LOOP 128 
 int /*<<< orphan*/  WEBP_CHUNK_ANMF ; 
 int /*<<< orphan*/  WEBP_MUX_MEMORY_ERROR ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPFree (int*) ; 
 scalar_t__ WebPMalloc (size_t) ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPMuxDeleteChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPMuxGetChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  WebPMuxGetFrame (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * WebPMuxNew () ; 
 int /*<<< orphan*/  WebPMuxNumChunks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WebPMuxPushFrame (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  WebPMuxSetAnimationParams (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  WebPMuxSetChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int WriteData (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int WriteWebP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int* kDescriptions ; 
 int /*<<< orphan*/ * kFourccList ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int Process(const Config* config) {
  WebPMux* mux = NULL;
  WebPData chunk;
  WebPMuxError err = WEBP_MUX_OK;
  int ok = 1;

  switch (config->action_type_) {
    case ACTION_GET: {
      ok = CreateMux(config->input_, &mux);
      if (!ok) goto Err2;
      switch (config->type_) {
        case FEATURE_ANMF:
          ok = GetFrame(mux, config);
          break;

        case FEATURE_ICCP:
        case FEATURE_EXIF:
        case FEATURE_XMP:
          err = WebPMuxGetChunk(mux, kFourccList[config->type_], &chunk);
          if (err != WEBP_MUX_OK) {
            ERROR_GOTO3("ERROR (%s): Could not get the %s.\n",
                        ErrorString(err), kDescriptions[config->type_], Err2);
          }
          ok = WriteData(config->output_, &chunk);
          break;

        default:
          ERROR_GOTO1("ERROR: Invalid feature for action 'get'.\n", Err2);
          break;
      }
      break;
    }
    case ACTION_SET: {
      switch (config->type_) {
        case FEATURE_ANMF: {
          int i;
          WebPMuxAnimParams params = { 0xFFFFFFFF, 0 };
          mux = WebPMuxNew();
          if (mux == NULL) {
            ERROR_GOTO2("ERROR (%s): Could not allocate a mux object.\n",
                        ErrorString(WEBP_MUX_MEMORY_ERROR), Err2);
          }
          for (i = 0; i < config->arg_count_; ++i) {
            switch (config->args_[i].subtype_) {
              case SUBTYPE_BGCOLOR: {
                uint32_t bgcolor;
                ok = ParseBgcolorArgs(config->args_[i].params_, &bgcolor);
                if (!ok) {
                  ERROR_GOTO1("ERROR: Could not parse the background color \n",
                              Err2);
                }
                params.bgcolor = bgcolor;
                break;
              }
              case SUBTYPE_LOOP: {
                int parse_error = 0;
                const int loop_count =
                    ExUtilGetInt(config->args_[i].params_, 10, &parse_error);
                if (loop_count < 0 || loop_count > 65535) {
                  // Note: This is only a 'necessary' condition for loop_count
                  // to be valid. The 'sufficient' conditioned in checked in
                  // WebPMuxSetAnimationParams() method called later.
                  ERROR_GOTO1("ERROR: Loop count must be in the range 0 to "
                              "65535.\n", Err2);
                }
                ok = !parse_error;
                if (!ok) goto Err2;
                params.loop_count = loop_count;
                break;
              }
              case SUBTYPE_ANMF: {
                WebPMuxFrameInfo frame;
                frame.id = WEBP_CHUNK_ANMF;
                ok = ExUtilReadFileToWebPData(config->args_[i].filename_,
                                              &frame.bitstream);
                if (!ok) goto Err2;
                ok = ParseFrameArgs(config->args_[i].params_, &frame);
                if (!ok) {
                  WebPDataClear(&frame.bitstream);
                  ERROR_GOTO1("ERROR: Could not parse frame properties.\n",
                              Err2);
                }
                err = WebPMuxPushFrame(mux, &frame, 1);
                WebPDataClear(&frame.bitstream);
                if (err != WEBP_MUX_OK) {
                  ERROR_GOTO3("ERROR (%s): Could not add a frame at index %d."
                              "\n", ErrorString(err), i, Err2);
                }
                break;
              }
              default: {
                ERROR_GOTO1("ERROR: Invalid subtype for 'frame'", Err2);
                break;
              }
            }
          }
          err = WebPMuxSetAnimationParams(mux, &params);
          if (err != WEBP_MUX_OK) {
            ERROR_GOTO2("ERROR (%s): Could not set animation parameters.\n",
                        ErrorString(err), Err2);
          }
          break;
        }

        case FEATURE_ICCP:
        case FEATURE_EXIF:
        case FEATURE_XMP: {
          ok = CreateMux(config->input_, &mux);
          if (!ok) goto Err2;
          ok = ExUtilReadFileToWebPData(config->args_[0].filename_, &chunk);
          if (!ok) goto Err2;
          err = WebPMuxSetChunk(mux, kFourccList[config->type_], &chunk, 1);
          free((void*)chunk.bytes);
          if (err != WEBP_MUX_OK) {
            ERROR_GOTO3("ERROR (%s): Could not set the %s.\n",
                        ErrorString(err), kDescriptions[config->type_], Err2);
          }
          break;
        }
        default: {
          ERROR_GOTO1("ERROR: Invalid feature for action 'set'.\n", Err2);
          break;
        }
      }
      ok = WriteWebP(mux, config->output_);
      break;
    }
    case ACTION_DURATION: {
      int num_frames;
      ok = CreateMux(config->input_, &mux);
      if (!ok) goto Err2;
      err = WebPMuxNumChunks(mux, WEBP_CHUNK_ANMF, &num_frames);
      ok = (err == WEBP_MUX_OK);
      if (!ok) {
        ERROR_GOTO1("ERROR: can not parse the number of frames.\n", Err2);
      }
      if (num_frames == 0) {
        fprintf(stderr, "Doesn't look like the source is animated. "
                        "Skipping duration setting.\n");
        ok = WriteWebP(mux, config->output_);
        if (!ok) goto Err2;
      } else {
        int i;
        int* durations = NULL;
        WebPMux* new_mux = DuplicateMuxHeader(mux);
        if (new_mux == NULL) goto Err2;
        durations = (int*)WebPMalloc((size_t)num_frames * sizeof(*durations));
        if (durations == NULL) goto Err2;
        for (i = 0; i < num_frames; ++i) durations[i] = -1;

        // Parse intervals to process.
        for (i = 0; i < config->arg_count_; ++i) {
          int k;
          int args[3];
          int duration, start, end;
          const int nb_args = ExUtilGetInts(config->args_[i].params_,
                                            10, 3, args);
          ok = (nb_args >= 1);
          if (!ok) goto Err3;
          duration = args[0];
          if (duration < 0) {
            ERROR_GOTO1("ERROR: duration must be strictly positive.\n", Err3);
          }

          if (nb_args == 1) {   // only duration is present -> use full interval
            start = 1;
            end = num_frames;
          } else {
            start = args[1];
            if (start <= 0) {
              start = 1;
            } else if (start > num_frames) {
              start = num_frames;
            }
            end = (nb_args >= 3) ? args[2] : start;
            if (end == 0 || end > num_frames) end = num_frames;
          }

          for (k = start; k <= end; ++k) {
            assert(k >= 1 && k <= num_frames);
            durations[k - 1] = duration;
          }
        }

        // Apply non-negative durations to their destination frames.
        for (i = 1; i <= num_frames; ++i) {
          WebPMuxFrameInfo frame;
          err = WebPMuxGetFrame(mux, i, &frame);
          if (err != WEBP_MUX_OK || frame.id != WEBP_CHUNK_ANMF) {
            ERROR_GOTO2("ERROR: can not retrieve frame #%d.\n", i, Err3);
          }
          if (durations[i - 1] >= 0) frame.duration = durations[i - 1];
          err = WebPMuxPushFrame(new_mux, &frame, 1);
          if (err != WEBP_MUX_OK) {
            ERROR_GOTO2("ERROR: error push frame data #%d\n", i, Err3);
          }
          WebPDataClear(&frame.bitstream);
        }
        WebPMuxDelete(mux);
        ok = WriteWebP(new_mux, config->output_);
        mux = new_mux;  // transfer for the WebPMuxDelete() call
        new_mux = NULL;

 Err3:
        WebPFree(durations);
        WebPMuxDelete(new_mux);
        if (!ok) goto Err2;
      }
      break;
    }
    case ACTION_STRIP: {
      ok = CreateMux(config->input_, &mux);
      if (!ok) goto Err2;
      if (config->type_ == FEATURE_ICCP || config->type_ == FEATURE_EXIF ||
          config->type_ == FEATURE_XMP) {
        err = WebPMuxDeleteChunk(mux, kFourccList[config->type_]);
        if (err != WEBP_MUX_OK) {
          ERROR_GOTO3("ERROR (%s): Could not strip the %s.\n",
                      ErrorString(err), kDescriptions[config->type_], Err2);
        }
      } else {
        ERROR_GOTO1("ERROR: Invalid feature for action 'strip'.\n", Err2);
        break;
      }
      ok = WriteWebP(mux, config->output_);
      break;
    }
    case ACTION_INFO: {
      ok = CreateMux(config->input_, &mux);
      if (!ok) goto Err2;
      ok = (DisplayInfo(mux) == WEBP_MUX_OK);
      break;
    }
    default: {
      assert(0);  // Invalid action.
      break;
    }
  }

 Err2:
  WebPMuxDelete(mux);
  return ok;
}