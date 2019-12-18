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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct TYPE_8__ {int ref_ntp; int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * blocks; void* last_seq; void* bad_seq; void* max_seq; scalar_t__ ref_rtp; scalar_t__ jitter; int /*<<< orphan*/  ssrc; } ;
typedef  TYPE_2__ rtp_source_t ;
struct TYPE_9__ {int ptc; TYPE_1__* ptv; } ;
typedef  TYPE_3__ rtp_session_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int UINT64_C (int) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rtp_source_t *
rtp_source_create (demux_t *demux, const rtp_session_t *session,
                   uint32_t ssrc, uint16_t init_seq)
{
    rtp_source_t *source;

    source = malloc (sizeof (*source) + (sizeof (void *) * session->ptc));
    if (source == NULL)
        return NULL;

    source->ssrc = ssrc;
    source->jitter = 0;
    source->ref_rtp = 0;
    source->ref_ntp = UINT64_C (1) << 62;
    source->max_seq = source->bad_seq = init_seq;
    source->last_seq = init_seq - 1;
    source->blocks = NULL;

    /* Initializes all payload */
    for (unsigned i = 0; i < session->ptc; i++)
        source->opaque[i] = session->ptv[i].init (demux);

    msg_Dbg (demux, "added RTP source (%08x)", ssrc);
    return source;
}