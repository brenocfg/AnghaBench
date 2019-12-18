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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  unsigned long int32_t ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_3__ {int height; int width; } ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  TYPE_1__ CvSize ;
typedef  int /*<<< orphan*/  CvMat ;

/* Variables and functions */
 int /*<<< orphan*/  CV_8UC3 ; 
 int YUV2B (int,int,int) ; 
 int YUV2G (int,int,int) ; 
 int YUV2R (int,int,int) ; 
 unsigned long abs (unsigned long) ; 
 int /*<<< orphan*/ * cvCreateImageHeader (TYPE_1__,int,int) ; 
 int /*<<< orphan*/ * cvGetImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvMat (int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cvShowImage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  vdout ; 

void t_toxav_receive_video_frame_cb(ToxAV *av, uint32_t friend_number,
                                    uint16_t width, uint16_t height,
                                    uint8_t const *y, uint8_t const *u, uint8_t const *v,
                                    int32_t ystride, int32_t ustride, int32_t vstride,
                                    void *user_data)
{
    ystride = abs(ystride);
    ustride = abs(ustride);
    vstride = abs(vstride);

    uint16_t *img_data = malloc(height * width * 6);

    unsigned long int i, j;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            uint8_t *point = (uint8_t *) img_data + 3 * ((i * width) + j);
            int yx = y[(i * ystride) + j];
            int ux = u[((i / 2) * ustride) + (j / 2)];
            int vx = v[((i / 2) * vstride) + (j / 2)];

            point[0] = YUV2R(yx, ux, vx);
            point[1] = YUV2G(yx, ux, vx);
            point[2] = YUV2B(yx, ux, vx);
        }
    }


    CvMat mat = cvMat(height, width, CV_8UC3, img_data);

    CvSize sz = {.height = height, .width = width};

    IplImage *header = cvCreateImageHeader(sz, 1, 3);
    IplImage *img = cvGetImage(&mat, header);
    cvShowImage(vdout, img);
    free(img_data);
}