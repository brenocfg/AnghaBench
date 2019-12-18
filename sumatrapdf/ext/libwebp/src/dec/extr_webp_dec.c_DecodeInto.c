#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_27__ {size_t data_size; int have_all_data; int offset; int /*<<< orphan*/  alpha_data_size; int /*<<< orphan*/  alpha_data; int /*<<< orphan*/  is_lossless; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ WebPHeaderStructure ;
struct TYPE_28__ {int /*<<< orphan*/  output; TYPE_9__* options; } ;
typedef  TYPE_2__ WebPDecParams ;
typedef  scalar_t__ VP8StatusCode ;
struct TYPE_29__ {scalar_t__ status_; } ;
typedef  TYPE_3__ VP8LDecoder ;
struct TYPE_30__ {int data_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ VP8Io ;
struct TYPE_31__ {scalar_t__ status_; int /*<<< orphan*/  mt_method_; int /*<<< orphan*/  alpha_data_size_; int /*<<< orphan*/  alpha_data_; } ;
typedef  TYPE_5__ VP8Decoder ;
struct TYPE_32__ {scalar_t__ flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  VP8Decode (TYPE_5__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  VP8Delete (TYPE_5__* const) ; 
 int /*<<< orphan*/  VP8GetHeaders (TYPE_5__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  VP8GetThreadMethod (TYPE_9__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8InitDithering (TYPE_9__*,TYPE_5__* const) ; 
 int /*<<< orphan*/  VP8InitIo (TYPE_4__*) ; 
 int /*<<< orphan*/  VP8LDecodeHeader (TYPE_3__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  VP8LDecodeImage (TYPE_3__* const) ; 
 int /*<<< orphan*/  VP8LDelete (TYPE_3__* const) ; 
 TYPE_3__* VP8LNew () ; 
 TYPE_5__* VP8New () ; 
 scalar_t__ VP8_STATUS_OK ; 
 scalar_t__ VP8_STATUS_OUT_OF_MEMORY ; 
 scalar_t__ WebPAllocateDecBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ WebPFlipBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPFreeDecBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPInitCustomIo (TYPE_2__* const,TYPE_4__*) ; 
 scalar_t__ WebPParseHeaders (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VP8StatusCode DecodeInto(const uint8_t* const data, size_t data_size,
                                WebPDecParams* const params) {
  VP8StatusCode status;
  VP8Io io;
  WebPHeaderStructure headers;

  headers.data = data;
  headers.data_size = data_size;
  headers.have_all_data = 1;
  status = WebPParseHeaders(&headers);   // Process Pre-VP8 chunks.
  if (status != VP8_STATUS_OK) {
    return status;
  }

  assert(params != NULL);
  VP8InitIo(&io);
  io.data = headers.data + headers.offset;
  io.data_size = headers.data_size - headers.offset;
  WebPInitCustomIo(params, &io);  // Plug the I/O functions.

  if (!headers.is_lossless) {
    VP8Decoder* const dec = VP8New();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    dec->alpha_data_ = headers.alpha_data;
    dec->alpha_data_size_ = headers.alpha_data_size;

    // Decode bitstream header, update io->width/io->height.
    if (!VP8GetHeaders(dec, &io)) {
      status = dec->status_;   // An error occurred. Grab error status.
    } else {
      // Allocate/check output buffers.
      status = WebPAllocateDecBuffer(io.width, io.height, params->options,
                                     params->output);
      if (status == VP8_STATUS_OK) {  // Decode
        // This change must be done before calling VP8Decode()
        dec->mt_method_ = VP8GetThreadMethod(params->options, &headers,
                                             io.width, io.height);
        VP8InitDithering(params->options, dec);
        if (!VP8Decode(dec, &io)) {
          status = dec->status_;
        }
      }
    }
    VP8Delete(dec);
  } else {
    VP8LDecoder* const dec = VP8LNew();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    if (!VP8LDecodeHeader(dec, &io)) {
      status = dec->status_;   // An error occurred. Grab error status.
    } else {
      // Allocate/check output buffers.
      status = WebPAllocateDecBuffer(io.width, io.height, params->options,
                                     params->output);
      if (status == VP8_STATUS_OK) {  // Decode
        if (!VP8LDecodeImage(dec)) {
          status = dec->status_;
        }
      }
    }
    VP8LDelete(dec);
  }

  if (status != VP8_STATUS_OK) {
    WebPFreeDecBuffer(params->output);
  } else {
    if (params->options != NULL && params->options->flip) {
      // This restores the original stride values if options->flip was used
      // during the call to WebPAllocateDecBuffer above.
      status = WebPFlipBuffer(params->output);
    }
  }
  return status;
}