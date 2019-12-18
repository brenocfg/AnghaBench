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
#define  ADDON_EXTENSION 134 
#define  ADDON_INTERFACE 133 
#define  ADDON_META 132 
#define  ADDON_PLAYLIST_PARSER 131 
#define  ADDON_SERVICE_DISCOVERY 130 
#define  ADDON_SKIN2 129 
#define  ADDON_UNKNOWN 128 

__attribute__((used)) static inline const char * getTypePsz( int i_type )
{
    switch( i_type )
    {
    case ADDON_PLAYLIST_PARSER:
        return "playlist";
    case ADDON_SKIN2:
        return "skin";
    case ADDON_SERVICE_DISCOVERY:
        return "discovery";
    case ADDON_EXTENSION:
        return "extension";
    case ADDON_INTERFACE:
        return "interface";
    case ADDON_META:
        return "meta";
    case ADDON_UNKNOWN:
    default:
        return "unknown";
    }
}