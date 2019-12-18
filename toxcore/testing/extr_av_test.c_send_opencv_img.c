#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_3__ {int height; int width; int /*<<< orphan*/ * imageData; } ;
typedef  TYPE_1__ IplImage ;

/* Variables and functions */
 int /*<<< orphan*/  RGB2U (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB2V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB2Y (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int toxav_video_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int send_opencv_img(ToxAV *av, uint32_t friend_number, const IplImage *img)
{
    int32_t strides[3] = { 1280, 640, 640 };
    uint8_t *planes[3] = {
        malloc(img->height * img->width),
        malloc(img->height * img->width / 4),
        malloc(img->height * img->width / 4),
    };

    int x_chroma_shift = 1;
    int y_chroma_shift = 1;

    int x, y;

    for (y = 0; y < img->height; ++y) {
        for (x = 0; x < img->width; ++x) {
            uint8_t r = img->imageData[(x + y * img->width) * 3 + 0];
            uint8_t g = img->imageData[(x + y * img->width) * 3 + 1];
            uint8_t b = img->imageData[(x + y * img->width) * 3 + 2];

            planes[0][x + y * strides[0]] = RGB2Y(r, g, b);

            if (!(x % (1 << x_chroma_shift)) && !(y % (1 << y_chroma_shift))) {
                const int i = x / (1 << x_chroma_shift);
                const int j = y / (1 << y_chroma_shift);
                planes[1][i + j * strides[1]] = RGB2U(r, g, b);
                planes[2][i + j * strides[2]] = RGB2V(r, g, b);
            }
        }
    }

    int rc = toxav_video_send_frame(av, friend_number, img->width, img->height,
                                    planes[0], planes[1], planes[2], NULL);
    free(planes[0]);
    free(planes[1]);
    free(planes[2]);
    return rc;
}