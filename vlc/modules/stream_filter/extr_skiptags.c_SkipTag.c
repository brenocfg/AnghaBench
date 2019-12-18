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
typedef  int /*<<< orphan*/  uint_fast64_t ;
typedef  scalar_t__ uint_fast32_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int ssize_t ;
struct TYPE_5__ {scalar_t__ i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 unsigned int MAX_TAGS ; 
 scalar_t__ MAX_TAG_SIZE ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* vlc_stream_Block (int /*<<< orphan*/ *,scalar_t__) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool SkipTag(stream_t *s, uint_fast32_t (*skipper)(stream_t *),
                    block_t **pp_block, unsigned *pi_tags_count)
{
    uint_fast64_t offset = vlc_stream_Tell(s);
    uint_fast32_t size = skipper(s);
    if(size> 0)
    {
        /* Skip the entire tag */
        ssize_t read;
        if(*pi_tags_count < MAX_TAGS && size <= MAX_TAG_SIZE)
        {
            *pp_block = vlc_stream_Block(s, size);
            read = *pp_block ? (ssize_t)(*pp_block)->i_buffer : -1;
        }
        else
        {
            read = vlc_stream_Read(s, NULL, size);
        }

        if(read < (ssize_t)size)
        {
            block_ChainRelease(*pp_block);
            *pp_block = NULL;
            if (unlikely(read < 0))
            {   /* I/O error, try to restore offset. If it fails, screwed. */
                if (vlc_stream_Seek(s, offset))
                    msg_Err(s, "seek failure");
                return false;
            }
        }
        else (*pi_tags_count)++;
    }
    return size != 0;
}