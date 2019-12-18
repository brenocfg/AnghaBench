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
typedef  int /*<<< orphan*/  WebPPicture ;

/* Variables and functions */
 int PictureARGBToYUVA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int) ; 
 int /*<<< orphan*/  WEBP_YUV420 ; 

int WebPPictureSharpARGBToYUVA(WebPPicture* picture) {
  return PictureARGBToYUVA(picture, WEBP_YUV420, 0.f, 1);
}