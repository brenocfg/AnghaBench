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

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 

__attribute__((used)) static const char *getMuxFromAlias( const char *psz_alias )
{
    static struct { const char alias[6]; const char mux[32]; } mux_alias[] =
    {
        { "avi", "avi" },
        { "ogg", "ogg" },
        { "ogm", "ogg" },
        { "ogv", "ogg" },
        { "flac","raw" },
        { "mp3", "raw" },
        { "mp4", "mp4" },
        { "mov", "mov" },
        { "moov","mov" },
        { "asf", "asf" },
        { "wma", "asf" },
        { "wmv", "asf" },
        { "trp", "ts" },
        { "ts",  "ts" },
        { "mpg", "ps" },
        { "mpeg","ps" },
        { "ps",  "ps" },
        { "mpeg1","mpeg1" },
        { "wav", "wav" },
        { "flv", "avformat{mux=flv}" },
        { "mkv", "avformat{mux=matroska}"},
        { "webm", "avformat{mux=webm}"},
    };

    if( !psz_alias )
        return NULL;

    for( size_t i = 0; i < sizeof mux_alias / sizeof *mux_alias; i++ )
        if( !strcasecmp( psz_alias, mux_alias[i].alias ) )
            return mux_alias[i].mux;

    return NULL;
}