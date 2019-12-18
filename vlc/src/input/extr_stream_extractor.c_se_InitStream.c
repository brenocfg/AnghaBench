#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  identifier; TYPE_1__* source; scalar_t__ pf_read; } ;
struct stream_extractor_private {TYPE_2__ extractor; } ;
struct TYPE_7__ {int /*<<< orphan*/  psz_url; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_block; int /*<<< orphan*/  pf_read; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  psz_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  StreamExtractorCreateMRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  se_StreamBlock ; 
 int /*<<< orphan*/  se_StreamControl ; 
 int /*<<< orphan*/  se_StreamRead ; 
 int /*<<< orphan*/  se_StreamSeek ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
se_InitStream( struct stream_extractor_private* priv, stream_t* s )
{
    if( priv->extractor.pf_read ) s->pf_read = se_StreamRead;
    else                          s->pf_block = se_StreamBlock;

    s->pf_seek = se_StreamSeek;
    s->pf_control = se_StreamControl;
    s->psz_url = StreamExtractorCreateMRL( priv->extractor.source->psz_url,
                                           priv->extractor.identifier );
    if( unlikely( !s->psz_url ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}