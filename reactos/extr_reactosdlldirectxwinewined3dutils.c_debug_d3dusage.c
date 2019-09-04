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
struct debug_buffer {int /*<<< orphan*/  str; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3DUSAGE_DEPTHSTENCIL ; 
 int WINED3DUSAGE_DMAP ; 
 int WINED3DUSAGE_DONOTCLIP ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int WINED3DUSAGE_LEGACY_CUBEMAP ; 
 int WINED3DUSAGE_NPATCHES ; 
 int WINED3DUSAGE_OVERLAY ; 
 int WINED3DUSAGE_OWNDC ; 
 int WINED3DUSAGE_POINTS ; 
 int WINED3DUSAGE_RENDERTARGET ; 
 int WINED3DUSAGE_RESTRICTED_CONTENT ; 
 int WINED3DUSAGE_RESTRICT_SHARED_RESOURCE ; 
 int WINED3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER ; 
 int WINED3DUSAGE_RTPATCHES ; 
 int WINED3DUSAGE_SOFTWAREPROCESSING ; 
 int WINED3DUSAGE_STATICDECL ; 
 int WINED3DUSAGE_TEXTAPI ; 
 int WINED3DUSAGE_TEXTURE ; 
 int WINED3DUSAGE_WRITEONLY ; 
 int /*<<< orphan*/  debug_append (struct debug_buffer*,char*,char*) ; 
 int /*<<< orphan*/  init_debug_buffer (struct debug_buffer*,char*) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ) ; 

const char *debug_d3dusage(DWORD usage)
{
    struct debug_buffer buffer;

    init_debug_buffer(&buffer, "0");
#define WINED3DUSAGE_TO_STR(x) if (usage & x) { debug_append(&buffer, #x, " | "); usage &= ~x; }
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_RENDERTARGET);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_DEPTHSTENCIL);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_WRITEONLY);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_SOFTWAREPROCESSING);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_DONOTCLIP);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_POINTS);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_RTPATCHES);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_NPATCHES);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_DYNAMIC);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_RESTRICTED_CONTENT);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_RESTRICT_SHARED_RESOURCE);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_DMAP);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_TEXTAPI);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_LEGACY_CUBEMAP);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_TEXTURE);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_OWNDC);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_STATICDECL);
    WINED3DUSAGE_TO_STR(WINED3DUSAGE_OVERLAY);
#undef WINED3DUSAGE_TO_STR
    if (usage)
        FIXME("Unrecognized usage flag(s) %#x.\n", usage);

    return wine_dbg_sprintf("%s", buffer.str);
}