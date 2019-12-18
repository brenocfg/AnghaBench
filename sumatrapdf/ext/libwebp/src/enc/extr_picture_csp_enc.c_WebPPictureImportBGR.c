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
typedef  int /*<<< orphan*/  WebPPicture ;

/* Variables and functions */
 int Import (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 

int WebPPictureImportBGR(WebPPicture* picture,
                         const uint8_t* rgb, int rgb_stride) {
  return (picture != NULL && rgb != NULL)
             ? Import(picture, rgb, rgb_stride, 3, 1, 0)
             : 0;
}