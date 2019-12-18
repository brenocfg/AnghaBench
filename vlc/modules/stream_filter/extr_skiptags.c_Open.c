#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ uint_fast64_t ;
struct skiptags_sys_t {TYPE_2__* p_tags; scalar_t__ header_skip; } ;
struct TYPE_7__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; struct skiptags_sys_t* p_sys; struct TYPE_7__* s; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {struct TYPE_8__* p_next; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 int /*<<< orphan*/  SkipAPETag ; 
 int /*<<< orphan*/  SkipID3Tag ; 
 scalar_t__ SkipTag (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**,unsigned int*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_2__*) ; 
 struct skiptags_sys_t* skiptags_sys_New () ; 
 scalar_t__ vlc_stream_Tell (TYPE_1__*) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    stream_t *stream = (stream_t *)obj;
    stream_t *s = stream->s;
    struct skiptags_sys_t *sys;

    block_t *p_tags = NULL, *p_tag = NULL;
    unsigned i_tagscount = 0;

    while (SkipTag(s, SkipID3Tag, &p_tag, &i_tagscount)||
           SkipTag(s, SkipAPETag, &p_tag, &i_tagscount))
    {
        if(p_tag)
        {
            p_tag->p_next = p_tags;
            p_tags = p_tag;
            p_tag = NULL;
        }
    }

    uint_fast64_t offset = vlc_stream_Tell(s);
    if (offset == 0 || !(sys = skiptags_sys_New()))
    {
        block_ChainRelease( p_tags );
        return VLC_EGENERIC; /* nothing to do */
    }

    sys->header_skip = offset;
    sys->p_tags = p_tags;
    stream->p_sys = sys;
    stream->pf_read = Read;
    stream->pf_seek = Seek;
    stream->pf_control = Control;
    return VLC_SUCCESS;
}