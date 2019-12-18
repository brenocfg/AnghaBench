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
struct TYPE_5__ {char* member_0; char* member_1; char const* name; } ;
typedef  TYPE_1__ demux_mapping ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* demux_lookup (char const*,TYPE_1__*,size_t) ; 

__attribute__((used)) static const char* DemuxNameFromExtension( char const* ext,
                                           bool b_preparsing )
{
    /* NOTE: Add only file without any problems here and with strong detection:
     * - no .mp3, .a52, ...
     *  - wav can't be added 'cause of a52 and dts in them as raw audio
     */
    static demux_mapping strong[] =
    { /* NOTE: must be sorted in asc order */
        { "aiff", "aiff" },
        { "asf",  "asf" },
        { "au",   "au" },
        { "avi",  "avi" },
        { "drc",  "dirac" },
        { "dv",   "dv" },
        { "flac", "flac" },
        { "h264", "h264" },
        { "kar", "smf" },
        { "m3u",  "m3u" },
        { "m4a",  "mp4" },
        { "m4v",  "m4v" },
        { "mid",  "smf" },
        { "mka",  "mkv" },
        { "mks",  "mkv" },
        { "mkv",  "mkv" },
        { "moov", "mp4" },
        { "mov",  "mp4" },
        { "mp4",  "mp4" },
        { "nsv",  "nsv" },
        { "oga",  "ogg" },
        { "ogg",  "ogg" },
        { "ogm",  "ogg" },
        { "ogv",  "ogg" },
        { "ogx",  "ogg" }, /*RFC5334*/
        { "opus", "ogg" }, /*draft-terriberry-oggopus-01*/
        { "pva",  "pva" },
        { "rm",   "avformat" },
        { "rmi",  "smf" },
        { "spx",  "ogg" },
        { "voc",  "voc" },
        { "wma",  "asf" },
        { "wmv",  "asf" },
    };

    /* Here, we don't mind if it does not work, it must be quick */
    static demux_mapping quick[] =
    { /* NOTE: shall be sorted in asc order */
        { "mp3", "mpga" },
        { "ogg", "ogg" },
        { "wma", "asf" },
    };

    struct {
        demux_mapping* data;
        size_t size;

    } lookup = {
        .data = b_preparsing ? quick : strong,
        .size = b_preparsing ? ARRAY_SIZE( quick ) : ARRAY_SIZE( strong )
    };

    demux_mapping* result = demux_lookup( ext, lookup.data, lookup.size );
    return result ? result->name : NULL;
}