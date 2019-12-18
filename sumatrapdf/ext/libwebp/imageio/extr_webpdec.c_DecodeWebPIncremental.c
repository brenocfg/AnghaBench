#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  WebPIDecoder ;
typedef  int /*<<< orphan*/  WebPDecoderConfig ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 int /*<<< orphan*/  PrintAnimationWarning (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8_STATUS_INVALID_PARAM ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  VP8_STATUS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/ * WebPIDecode (int /*<<< orphan*/  const* const,size_t,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  WebPIDelete (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  WebPIUpdate (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

VP8StatusCode DecodeWebPIncremental(
    const uint8_t* const data, size_t data_size,
    WebPDecoderConfig* const config) {
  VP8StatusCode status = VP8_STATUS_OK;
  if (config == NULL) return VP8_STATUS_INVALID_PARAM;

  PrintAnimationWarning(config);

  // Decoding call.
  {
    WebPIDecoder* const idec = WebPIDecode(data, data_size, config);
    if (idec == NULL) {
      fprintf(stderr, "Failed during WebPINewDecoder().\n");
      return VP8_STATUS_OUT_OF_MEMORY;
    } else {
      status = WebPIUpdate(idec, data, data_size);
      WebPIDelete(idec);
    }
  }
  return status;
}