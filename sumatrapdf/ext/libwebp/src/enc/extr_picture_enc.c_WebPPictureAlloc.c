#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  use_argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int WebPPictureAllocARGB (TYPE_1__*,int const,int const) ; 
 int WebPPictureAllocYUVA (TYPE_1__*,int const,int const) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 

int WebPPictureAlloc(WebPPicture* picture) {
  if (picture != NULL) {
    const int width = picture->width;
    const int height = picture->height;

    WebPPictureFree(picture);   // erase previous buffer

    if (!picture->use_argb) {
      return WebPPictureAllocYUVA(picture, width, height);
    } else {
      return WebPPictureAllocARGB(picture, width, height);
    }
  }
  return 1;
}