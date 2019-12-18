#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int use_argb; int width; int height; TYPE_2__* custom_ptr; int /*<<< orphan*/  writer; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_14__ {size_t size; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_2__ WebPMemoryWriter ;
struct TYPE_15__ {int lossless; } ;
typedef  TYPE_3__ WebPConfig ;
typedef  scalar_t__ (* Importer ) (TYPE_1__*,int /*<<< orphan*/  const*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_PRESET_DEFAULT ; 
 int /*<<< orphan*/  WebPConfigPreset (TYPE_3__*,int /*<<< orphan*/ ,float) ; 
 scalar_t__ WebPEncode (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  WebPMemoryWrite ; 
 int /*<<< orphan*/  WebPMemoryWriterClear (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPMemoryWriterInit (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureInit (TYPE_1__*) ; 

__attribute__((used)) static size_t Encode(const uint8_t* rgba, int width, int height, int stride,
                     Importer import, float quality_factor, int lossless,
                     uint8_t** output) {
  WebPPicture pic;
  WebPConfig config;
  WebPMemoryWriter wrt;
  int ok;

  if (output == NULL) return 0;

  if (!WebPConfigPreset(&config, WEBP_PRESET_DEFAULT, quality_factor) ||
      !WebPPictureInit(&pic)) {
    return 0;  // shouldn't happen, except if system installation is broken
  }

  config.lossless = !!lossless;
  pic.use_argb = !!lossless;
  pic.width = width;
  pic.height = height;
  pic.writer = WebPMemoryWrite;
  pic.custom_ptr = &wrt;
  WebPMemoryWriterInit(&wrt);

  ok = import(&pic, rgba, stride) && WebPEncode(&config, &pic);
  WebPPictureFree(&pic);
  if (!ok) {
    WebPMemoryWriterClear(&wrt);
    *output = NULL;
    return 0;
  }
  *output = wrt.mem;
  return wrt.size;
}