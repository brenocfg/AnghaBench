#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * stride; scalar_t__* planes; int /*<<< orphan*/  d_h; int /*<<< orphan*/  d_w; } ;
typedef  TYPE_2__ vpx_image_t ;
typedef  int /*<<< orphan*/ * vpx_codec_iter_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct RTPMessage {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  second; int /*<<< orphan*/  (* first ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  queue_mutex; TYPE_1__ vcb; int /*<<< orphan*/  friend_number; int /*<<< orphan*/  av; int /*<<< orphan*/  decoder; int /*<<< orphan*/  vbuf_raw; } ;
typedef  TYPE_3__ VCSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_DECODE_TIME_US ; 
 int VPX_CODEC_OK ; 
 int /*<<< orphan*/  free (struct RTPMessage*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ rb_read (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vpx_codec_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpx_codec_err_to_string (int) ; 
 TYPE_2__* vpx_codec_get_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vpx_img_free (TYPE_2__*) ; 

void vc_iterate(VCSession *vc)
{
    if (!vc)
        return;

    struct RTPMessage *p;
    int rc;

    pthread_mutex_lock(vc->queue_mutex);

    if (rb_read(vc->vbuf_raw, (void **)&p)) {
        pthread_mutex_unlock(vc->queue_mutex);

        rc = vpx_codec_decode(vc->decoder, p->data, p->len, NULL, MAX_DECODE_TIME_US);
        free(p);

        if (rc != VPX_CODEC_OK)
            LOGGER_ERROR("Error decoding video: %s", vpx_codec_err_to_string(rc));
        else {
            vpx_codec_iter_t iter = NULL;
            vpx_image_t *dest = vpx_codec_get_frame(vc->decoder, &iter);

            /* Play decoded images */
            for (; dest; dest = vpx_codec_get_frame(vc->decoder, &iter)) {
                if (vc->vcb.first)
                    vc->vcb.first(vc->av, vc->friend_number, dest->d_w, dest->d_h,
                                  (const uint8_t *)dest->planes[0], (const uint8_t *)dest->planes[1], (const uint8_t *)dest->planes[2],
                                  dest->stride[0], dest->stride[1], dest->stride[2], vc->vcb.second);

                vpx_img_free(dest);
            }
        }

        return;
    }

    pthread_mutex_unlock(vc->queue_mutex);
}