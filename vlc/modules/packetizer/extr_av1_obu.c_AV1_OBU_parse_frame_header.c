#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bs_t ;
typedef  int /*<<< orphan*/  av1_OBU_sequence_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  header; int /*<<< orphan*/  obu_header; } ;
typedef  TYPE_1__ av1_OBU_frame_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV1_release_frame_header (TYPE_1__*) ; 
 int /*<<< orphan*/  av1_parse_uncompressed_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av1_read_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 TYPE_1__* calloc (int,int) ; 

av1_OBU_frame_header_t *
    AV1_OBU_parse_frame_header(const uint8_t *p_data, size_t i_data,
                               const av1_OBU_sequence_header_t *p_seq)
{
    bs_t bs;
    bs_init(&bs, p_data, i_data);

    av1_OBU_frame_header_t *p_fh = calloc(1, sizeof(*p_fh));
    if(!p_fh)
        return NULL;

    if(!av1_read_header(&bs, &p_fh->obu_header) ||
       !av1_parse_uncompressed_header(&bs, &p_fh->header, p_seq))
    {
        AV1_release_frame_header(p_fh);
        return NULL;
    }

    return p_fh;
}