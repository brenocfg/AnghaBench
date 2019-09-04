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
struct TYPE_3__ {int /*<<< orphan*/  pack_swap_bytes; int /*<<< orphan*/  pack_lsb_first; int /*<<< orphan*/  pack_skip_pixels; int /*<<< orphan*/  pack_skip_rows; int /*<<< orphan*/  pack_row_length; int /*<<< orphan*/  pack_alignment; int /*<<< orphan*/  unpack_swap_bytes; int /*<<< orphan*/  unpack_lsb_first; int /*<<< orphan*/  unpack_skip_pixels; int /*<<< orphan*/  unpack_skip_rows; int /*<<< orphan*/  unpack_row_length; int /*<<< orphan*/  unpack_alignment; } ;
typedef  TYPE_1__ PixelStorageModes ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_PACK_LSB_FIRST ; 
 int /*<<< orphan*/  GL_PACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_PACK_SKIP_PIXELS ; 
 int /*<<< orphan*/  GL_PACK_SKIP_ROWS ; 
 int /*<<< orphan*/  GL_PACK_SWAP_BYTES ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNPACK_LSB_FIRST ; 
 int /*<<< orphan*/  GL_UNPACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_UNPACK_SKIP_PIXELS ; 
 int /*<<< orphan*/  GL_UNPACK_SKIP_ROWS ; 
 int /*<<< orphan*/  GL_UNPACK_SWAP_BYTES ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void retrieveStoreModes(PixelStorageModes *psm)
{
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &psm->unpack_alignment);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &psm->unpack_row_length);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &psm->unpack_skip_rows);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &psm->unpack_skip_pixels);
    glGetIntegerv(GL_UNPACK_LSB_FIRST, &psm->unpack_lsb_first);
    glGetIntegerv(GL_UNPACK_SWAP_BYTES, &psm->unpack_swap_bytes);

    glGetIntegerv(GL_PACK_ALIGNMENT, &psm->pack_alignment);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &psm->pack_row_length);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &psm->pack_skip_rows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &psm->pack_skip_pixels);
    glGetIntegerv(GL_PACK_LSB_FIRST, &psm->pack_lsb_first);
    glGetIntegerv(GL_PACK_SWAP_BYTES, &psm->pack_swap_bytes);
}