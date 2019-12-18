#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ subdivide; int left_in_frame; int left_in_block; int (* get_bytes ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  in_arg; } ;
typedef  TYPE_1__ lzx_data ;
struct TYPE_5__ {scalar_t__ user_data; } ;
typedef  TYPE_2__ lz_info ;

/* Variables and functions */
 int LZX_FRAME_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lzx_get_chars(lz_info *lzi, int n, u_char *buf)
{
  /* force lz compression to stop after every block */
  int chars_read;
  int chars_pad;

  lzx_data *lzud = (lzx_data *)lzi->user_data;
#ifdef OLDFRAMING
  if (lzud->subdivide < 0) return 0;
  if (n > lzud->left_in_frame)
    n = lzud->left_in_frame;
  if (n > lzud->left_in_block)
    n = lzud->left_in_block;
#endif
  chars_read = lzud->get_bytes(lzud->in_arg, n, buf);
#ifdef OLDFRAMING
  lzud->left_in_frame -= chars_read;
  lzud->left_in_block -= chars_read;
#else
  lzud->left_in_frame -= chars_read % LZX_FRAME_SIZE;
  if (lzud->left_in_frame < 0) 
    lzud->left_in_frame += LZX_FRAME_SIZE;
#endif
  if ((chars_read < n) && (lzud->left_in_frame)) {
    chars_pad = n - chars_read;
    if (chars_pad > lzud->left_in_frame) chars_pad = lzud->left_in_frame;
    /* never emit a full frame of padding.  This prevents silliness when
       lzx_compress is called when at EOF but EOF not yet detected */
    if (chars_pad == LZX_FRAME_SIZE) chars_pad = 0;
#ifdef OLDFRAMING
    if (chars_pad > lzud->left_in_block) chars_pad = lzud->left_in_block;
#endif
    memset(buf + chars_read, 0, chars_pad);
    lzud->left_in_frame -= chars_pad;
#ifdef OLDFRAMING
    lzud->left_in_block -= chars_pad;
#endif
    chars_read += chars_pad;
  }
  return chars_read;
}