#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct wl_shm_pool {int dummy; } ;
struct wl_buffer {int dummy; } ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {unsigned int width; int height; int pagemask; int done; int y; int x; int /*<<< orphan*/  display; int /*<<< orphan*/  output; int /*<<< orphan*/  screenshooter; int /*<<< orphan*/  shm; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {size_t p_buffer; size_t i_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  WL_SHM_FORMAT_XRGB8888 ; 
 TYPE_3__* block_File (int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ftruncate (int,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screenshooter_shoot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_buffer*) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_memfd () ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_buffer_destroy (struct wl_buffer*) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 struct wl_shm_pool* wl_shm_create_pool (int /*<<< orphan*/ ,int,size_t) ; 
 struct wl_buffer* wl_shm_pool_create_buffer (struct wl_shm_pool*,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shm_pool_destroy (struct wl_shm_pool*) ; 

__attribute__((used)) static block_t *Shoot(demux_t *demux)
{
    demux_sys_t *sys = demux->p_sys;

    int fd = vlc_memfd();
    if (fd == -1)
    {
        msg_Err(demux, "buffer creation error: %s", vlc_strerror_c(errno));
        return NULL;
    }

    /* NOTE: one extra line for overflow if screen-left > 0 */
    uint32_t pitch = 4u * sys->width;
    size_t size = (pitch * (sys->height + 1) + sys->pagemask) & ~sys->pagemask;
    block_t *block = NULL;

    if (ftruncate(fd, size) < 0)
    {
        msg_Err(demux, "buffer allocation error: %s", vlc_strerror_c(errno));
        goto out;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(sys->shm, fd, size);
    if (pool == NULL)
        goto out;

    struct wl_buffer *buffer;
    buffer = wl_shm_pool_create_buffer(pool, 0, sys->width, sys->height,
                                       pitch, WL_SHM_FORMAT_XRGB8888);
    wl_shm_pool_destroy(pool);
    if (buffer == NULL)
        goto out;

    sys->done = false;
    screenshooter_shoot(sys->screenshooter, sys->output, buffer);

    while (!sys->done)
        wl_display_roundtrip(sys->display);

    wl_buffer_destroy(buffer);
    block = block_File(fd, true);

    if (block != NULL)
    {
        size_t skip = (sys->y * sys->width + sys->x) * 4;

        block->p_buffer += skip;
        block->i_buffer -= skip;
    }

out:
    vlc_close(fd);
    return block;
}