#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ WebPData ;
typedef  int /*<<< orphan*/  W_CHAR ;
typedef  int /*<<< orphan*/  AnimatedImage ;

/* Variables and functions */
 int /*<<< orphan*/  ClearAnimatedImage (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ImgIoUtilReadFile (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsGIF (TYPE_1__*) ; 
 scalar_t__ IsWebP (TYPE_1__*) ; 
 int ReadAnimatedGIF (char const*,int /*<<< orphan*/ * const,int,char const*) ; 
 int ReadAnimatedWebP (char const*,TYPE_1__*,int /*<<< orphan*/ * const,int,char const*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPDataClear (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

int ReadAnimatedImage(const char filename[], AnimatedImage* const image,
                      int dump_frames, const char dump_folder[]) {
  int ok = 0;
  WebPData webp_data;

  WebPDataInit(&webp_data);
  memset(image, 0, sizeof(*image));

  if (!ImgIoUtilReadFile(filename, &webp_data.bytes, &webp_data.size)) {
    WFPRINTF(stderr, "Error reading file: %s\n", (const W_CHAR*)filename);
    return 0;
  }

  if (IsWebP(&webp_data)) {
    ok = ReadAnimatedWebP(filename, &webp_data, image, dump_frames,
                          dump_folder);
  } else if (IsGIF(&webp_data)) {
    ok = ReadAnimatedGIF(filename, image, dump_frames, dump_folder);
  } else {
    WFPRINTF(stderr,
             "Unknown file type: %s. Supported file types are WebP and GIF\n",
             (const W_CHAR*)filename);
    ok = 0;
  }
  if (!ok) ClearAnimatedImage(image);
  WebPDataClear(&webp_data);
  return ok;
}