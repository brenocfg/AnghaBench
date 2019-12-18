#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
#define  DESC_CLEAN_AUDIO_HEARING_IMPAIRED 130 
#define  DESC_CLEAN_EFFECTS 129 
#define  DESC_VISUAL_IMPAIRED_COMMENTS 128 
 char* strdup (char const*) ; 

__attribute__((used)) static char *GetIso639AudioTypeDesc( uint8_t type )
{
    static const char *audio_type[] = {
        /* "Main audio", */
        DESC_CLEAN_EFFECTS,
        DESC_CLEAN_AUDIO_HEARING_IMPAIRED,
        DESC_VISUAL_IMPAIRED_COMMENTS,
    };

    if ( type == 0 || type >= ARRAY_SIZE(audio_type) )
        return NULL;

    return strdup( audio_type[ --type ] );
}