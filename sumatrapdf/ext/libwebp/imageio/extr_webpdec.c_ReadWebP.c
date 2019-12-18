#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_18__ {int width; int height; int* argb; int argb_stride; int y_stride; int uv_stride; int a_stride; scalar_t__ use_argb; int /*<<< orphan*/ * a; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_4__ WebPPicture ;
struct TYPE_21__ {int width; int height; int /*<<< orphan*/  has_alpha; } ;
struct TYPE_16__ {int y_stride; int u_stride; int v_stride; int a_stride; int y_size; int u_size; int v_size; int a_size; int /*<<< orphan*/ * a; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y; } ;
struct TYPE_15__ {int stride; int size; int /*<<< orphan*/ * rgba; } ;
struct TYPE_17__ {TYPE_2__ YUVA; TYPE_1__ RGBA; } ;
struct TYPE_20__ {int is_external_memory; TYPE_3__ u; int /*<<< orphan*/  colorspace; } ;
struct TYPE_19__ {TYPE_7__ input; TYPE_6__ output; } ;
typedef  TYPE_5__ WebPDecoderConfig ;
typedef  TYPE_6__ WebPDecBuffer ;
typedef  TYPE_7__ WebPBitstreamFeatures ;
typedef  scalar_t__ VP8StatusCode ;
typedef  int /*<<< orphan*/  Metadata ;

/* Variables and functions */
 scalar_t__ DecodeWebP (int /*<<< orphan*/  const* const,size_t,TYPE_5__*) ; 
 int ExtractMetadata (int /*<<< orphan*/  const* const,size_t,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ImgIoUtilCheckSizeArgumentsOverflow (int,int) ; 
 int /*<<< orphan*/  MODE_ARGB ; 
 int /*<<< orphan*/  MODE_BGRA ; 
 int /*<<< orphan*/  MODE_YUV ; 
 int /*<<< orphan*/  MODE_YUVA ; 
 int /*<<< orphan*/  PrintWebPError (char*,scalar_t__) ; 
 scalar_t__ VP8_STATUS_BITSTREAM_ERROR ; 
 scalar_t__ VP8_STATUS_OK ; 
 scalar_t__ VP8_STATUS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  WEBP_YUV420 ; 
 int /*<<< orphan*/  WEBP_YUV420A ; 
 int /*<<< orphan*/  WebPFreeDecBuffer (TYPE_6__* const) ; 
 scalar_t__ WebPGetFeatures (int /*<<< orphan*/  const* const,size_t,TYPE_7__* const) ; 
 int /*<<< orphan*/  WebPInitDecoderConfig (TYPE_5__*) ; 
 int WebPPictureAlloc (TYPE_4__* const) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_4__* const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int ReadWebP(const uint8_t* const data, size_t data_size,
             WebPPicture* const pic,
             int keep_alpha, Metadata* const metadata) {
  int ok = 0;
  VP8StatusCode status = VP8_STATUS_OK;
  WebPDecoderConfig config;
  WebPDecBuffer* const output_buffer = &config.output;
  WebPBitstreamFeatures* const bitstream = &config.input;

  if (data == NULL || data_size == 0 || pic == NULL) return 0;

  if (!WebPInitDecoderConfig(&config)) {
    fprintf(stderr, "Library version mismatch!\n");
    return 0;
  }

  status = WebPGetFeatures(data, data_size, bitstream);
  if (status != VP8_STATUS_OK) {
    PrintWebPError("input data", status);
    return 0;
  }

  do {
    const int has_alpha = keep_alpha && bitstream->has_alpha;
    uint64_t stride;
    pic->width = bitstream->width;
    pic->height = bitstream->height;
    if (pic->use_argb) {
      stride = (uint64_t)bitstream->width * 4;
    } else {
      stride = (uint64_t)bitstream->width * (has_alpha ? 5 : 3) / 2;
      pic->colorspace = has_alpha ? WEBP_YUV420A : WEBP_YUV420;
    }

    if (!ImgIoUtilCheckSizeArgumentsOverflow(stride, bitstream->height)) {
      status = VP8_STATUS_OUT_OF_MEMORY;
      break;
    }

    ok = WebPPictureAlloc(pic);
    if (!ok) {
      status = VP8_STATUS_OUT_OF_MEMORY;
      break;
    }
    if (pic->use_argb) {
#ifdef WORDS_BIGENDIAN
      output_buffer->colorspace = MODE_ARGB;
#else
      output_buffer->colorspace = MODE_BGRA;
#endif
      output_buffer->u.RGBA.rgba = (uint8_t*)pic->argb;
      output_buffer->u.RGBA.stride = pic->argb_stride * sizeof(uint32_t);
      output_buffer->u.RGBA.size = output_buffer->u.RGBA.stride * pic->height;
    } else {
      output_buffer->colorspace = has_alpha ? MODE_YUVA : MODE_YUV;
      output_buffer->u.YUVA.y = pic->y;
      output_buffer->u.YUVA.u = pic->u;
      output_buffer->u.YUVA.v = pic->v;
      output_buffer->u.YUVA.a = has_alpha ? pic->a : NULL;
      output_buffer->u.YUVA.y_stride = pic->y_stride;
      output_buffer->u.YUVA.u_stride = pic->uv_stride;
      output_buffer->u.YUVA.v_stride = pic->uv_stride;
      output_buffer->u.YUVA.a_stride = has_alpha ? pic->a_stride : 0;
      output_buffer->u.YUVA.y_size = pic->height * pic->y_stride;
      output_buffer->u.YUVA.u_size = (pic->height + 1) / 2 * pic->uv_stride;
      output_buffer->u.YUVA.v_size = (pic->height + 1) / 2 * pic->uv_stride;
      output_buffer->u.YUVA.a_size = pic->height * pic->a_stride;
    }
    output_buffer->is_external_memory = 1;

    status = DecodeWebP(data, data_size, &config);
    ok = (status == VP8_STATUS_OK);
    if (ok && !keep_alpha && pic->use_argb) {
      // Need to wipe out the alpha value, as requested.
      int x, y;
      uint32_t* argb = pic->argb;
      for (y = 0; y < pic->height; ++y) {
        for (x = 0; x < pic->width; ++x) argb[x] |= 0xff000000u;
        argb += pic->argb_stride;
      }
    }
  } while (0);   // <- so we can 'break' out of the loop

  if (status != VP8_STATUS_OK) {
    PrintWebPError("input data", status);
    ok = 0;
  }

  WebPFreeDecBuffer(output_buffer);

  if (ok && metadata != NULL) {
    ok = ExtractMetadata(data, data_size, metadata);
    if (!ok) {
      PrintWebPError("metadata", VP8_STATUS_BITSTREAM_ERROR);
    }
  }
  if (!ok) WebPPictureFree(pic);
  return ok;
}