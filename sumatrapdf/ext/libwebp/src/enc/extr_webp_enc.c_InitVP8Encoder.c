#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_16__ {scalar_t__ filter_strength; scalar_t__ autofilter; float quality; int pass; int partitions; int filter_type; } ;
typedef  TYPE_2__ WebPConfig ;
typedef  int /*<<< orphan*/  VP8SegmentInfo ;
typedef  int /*<<< orphan*/  VP8ModeScore ;
typedef  int /*<<< orphan*/  VP8MBInfo ;
struct TYPE_17__ {int num_parts_; int mb_w_; int mb_h_; int preds_w_; int profile_; int /*<<< orphan*/  tokens_; scalar_t__ percent_; TYPE_1__* pic_; TYPE_2__* config_; int /*<<< orphan*/ * top_derr_; int /*<<< orphan*/ * y_top_; int /*<<< orphan*/ * uv_top_; int /*<<< orphan*/ * lf_stats_; int /*<<< orphan*/ * nz_; int /*<<< orphan*/ * preds_; int /*<<< orphan*/ * mb_info_; } ;
typedef  TYPE_3__ VP8Encoder ;
typedef  int /*<<< orphan*/  VP8EncProba ;
typedef  int /*<<< orphan*/  VP8EncIterator ;
typedef  int /*<<< orphan*/  LFStats ;
typedef  int /*<<< orphan*/  DError ;

/* Variables and functions */
 float ERROR_DIFFUSION_QUALITY ; 
 int /*<<< orphan*/  MapConfigToTools (TYPE_3__*) ; 
 int /*<<< orphan*/  ResetBoundaryPredictions (TYPE_3__*) ; 
 int /*<<< orphan*/  ResetFilterHeader (TYPE_3__*) ; 
 int /*<<< orphan*/  ResetSegmentHeader (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8DefaultProbas (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8EncDspCostInit () ; 
 int /*<<< orphan*/  VP8EncDspInit () ; 
 int /*<<< orphan*/  VP8EncInitAlpha (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8TBufferInit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ WEBP_ALIGN (int /*<<< orphan*/ *) ; 
 int const WEBP_ALIGN_CST ; 
 int /*<<< orphan*/  WebPEncodingSetError (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 scalar_t__ WebPSafeMalloc (int const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static VP8Encoder* InitVP8Encoder(const WebPConfig* const config,
                                  WebPPicture* const picture) {
  VP8Encoder* enc;
  const int use_filter =
      (config->filter_strength > 0) || (config->autofilter > 0);
  const int mb_w = (picture->width + 15) >> 4;
  const int mb_h = (picture->height + 15) >> 4;
  const int preds_w = 4 * mb_w + 1;
  const int preds_h = 4 * mb_h + 1;
  const size_t preds_size = preds_w * preds_h * sizeof(*enc->preds_);
  const int top_stride = mb_w * 16;
  const size_t nz_size = (mb_w + 1) * sizeof(*enc->nz_) + WEBP_ALIGN_CST;
  const size_t info_size = mb_w * mb_h * sizeof(*enc->mb_info_);
  const size_t samples_size =
      2 * top_stride * sizeof(*enc->y_top_)  // top-luma/u/v
      + WEBP_ALIGN_CST;                      // align all
  const size_t lf_stats_size =
      config->autofilter ? sizeof(*enc->lf_stats_) + WEBP_ALIGN_CST : 0;
  const size_t top_derr_size =
      (config->quality <= ERROR_DIFFUSION_QUALITY || config->pass > 1) ?
          mb_w * sizeof(*enc->top_derr_) : 0;
  uint8_t* mem;
  const uint64_t size = (uint64_t)sizeof(*enc)   // main struct
                      + WEBP_ALIGN_CST           // cache alignment
                      + info_size                // modes info
                      + preds_size               // prediction modes
                      + samples_size             // top/left samples
                      + top_derr_size            // top diffusion error
                      + nz_size                  // coeff context bits
                      + lf_stats_size;           // autofilter stats

#ifdef PRINT_MEMORY_INFO
  printf("===================================\n");
  printf("Memory used:\n"
         "             encoder: %ld\n"
         "                info: %ld\n"
         "               preds: %ld\n"
         "         top samples: %ld\n"
         "       top diffusion: %ld\n"
         "            non-zero: %ld\n"
         "            lf-stats: %ld\n"
         "               total: %ld\n",
         sizeof(*enc) + WEBP_ALIGN_CST, info_size,
         preds_size, samples_size, top_derr_size, nz_size, lf_stats_size, size);
  printf("Transient object sizes:\n"
         "      VP8EncIterator: %ld\n"
         "        VP8ModeScore: %ld\n"
         "      VP8SegmentInfo: %ld\n"
         "         VP8EncProba: %ld\n"
         "             LFStats: %ld\n",
         sizeof(VP8EncIterator), sizeof(VP8ModeScore),
         sizeof(VP8SegmentInfo), sizeof(VP8EncProba),
         sizeof(LFStats));
  printf("Picture size (yuv): %ld\n",
         mb_w * mb_h * 384 * sizeof(uint8_t));
  printf("===================================\n");
#endif
  mem = (uint8_t*)WebPSafeMalloc(size, sizeof(*mem));
  if (mem == NULL) {
    WebPEncodingSetError(picture, VP8_ENC_ERROR_OUT_OF_MEMORY);
    return NULL;
  }
  enc = (VP8Encoder*)mem;
  mem = (uint8_t*)WEBP_ALIGN(mem + sizeof(*enc));
  memset(enc, 0, sizeof(*enc));
  enc->num_parts_ = 1 << config->partitions;
  enc->mb_w_ = mb_w;
  enc->mb_h_ = mb_h;
  enc->preds_w_ = preds_w;
  enc->mb_info_ = (VP8MBInfo*)mem;
  mem += info_size;
  enc->preds_ = mem + 1 + enc->preds_w_;
  mem += preds_size;
  enc->nz_ = 1 + (uint32_t*)WEBP_ALIGN(mem);
  mem += nz_size;
  enc->lf_stats_ = lf_stats_size ? (LFStats*)WEBP_ALIGN(mem) : NULL;
  mem += lf_stats_size;

  // top samples (all 16-aligned)
  mem = (uint8_t*)WEBP_ALIGN(mem);
  enc->y_top_ = mem;
  enc->uv_top_ = enc->y_top_ + top_stride;
  mem += 2 * top_stride;
  enc->top_derr_ = top_derr_size ? (DError*)mem : NULL;
  mem += top_derr_size;
  assert(mem <= (uint8_t*)enc + size);

  enc->config_ = config;
  enc->profile_ = use_filter ? ((config->filter_type == 1) ? 0 : 1) : 2;
  enc->pic_ = picture;
  enc->percent_ = 0;

  MapConfigToTools(enc);
  VP8EncDspInit();
  VP8DefaultProbas(enc);
  ResetSegmentHeader(enc);
  ResetFilterHeader(enc);
  ResetBoundaryPredictions(enc);
  VP8EncDspCostInit();
  VP8EncInitAlpha(enc);

  // lower quality means smaller output -> we modulate a little the page
  // size based on quality. This is just a crude 1rst-order prediction.
  {
    const float scale = 1.f + config->quality * 5.f / 100.f;  // in [1,6]
    VP8TBufferInit(&enc->tokens_, (int)(mb_w * mb_h * 4 * scale));
  }
  return enc;
}