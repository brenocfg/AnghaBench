#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  size_t ssize_t ;
struct TYPE_4__ {size_t marker_size; int /*<<< orphan*/  codec; int /*<<< orphan*/  marker; scalar_t__ (* detect ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ image_format_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* formats ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 size_t vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_fourcc_t Detect(stream_t *s)
{
    const uint8_t *peek;
    size_t peek_size = 0;

    for (size_t i = 0; i < ARRAY_SIZE(formats); i++) {
        const image_format_t *img = &formats[i];

        if (img->detect != NULL) {
            if (img->detect(s))
                return img->codec;

            if (vlc_stream_Seek(s, 0))
               return 0;

            /* Seeking invalidates the current peek buffer */
            peek_size = 0;
            continue;
        }

        if (peek_size < img->marker_size) {
            ssize_t val = vlc_stream_Peek(s, &peek, img->marker_size);
            if (val < 0)
                continue;
            peek_size = val;
        }

        assert(img->marker_size > 0); /* ensure peek is a valid pointer */

        if (peek_size >= img->marker_size
         && memcmp(peek, img->marker, img->marker_size) == 0)
            return img->codec;
    }
    return 0;
}