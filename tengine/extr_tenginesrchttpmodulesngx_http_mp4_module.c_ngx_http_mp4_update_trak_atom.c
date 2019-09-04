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
typedef  int /*<<< orphan*/  ngx_mp4_atom_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  pos; } ;
struct TYPE_4__ {int size; TYPE_2__ trak_atom_buf; } ;
typedef  TYPE_1__ ngx_http_mp4_trak_t ;
typedef  int /*<<< orphan*/  ngx_http_mp4_file_t ;
typedef  TYPE_2__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ngx_http_mp4_update_trak_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    ngx_buf_t  *atom;

    trak->size += sizeof(ngx_mp4_atom_header_t);
    atom = &trak->trak_atom_buf;
    ngx_mp4_set_32value(atom->pos, trak->size);
}