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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibraryW (char const*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 void* pgluDeleteTess ; 
 void* pgluNewTess ; 
 void* pgluTessBeginContour ; 
 void* pgluTessBeginPolygon ; 
 void* pgluTessCallback ; 
 void* pgluTessEndContour ; 
 void* pgluTessEndPolygon ; 
 void* pgluTessNormal ; 
 void* pgluTessVertex ; 

__attribute__((used)) static HMODULE load_libglu(void)
{
    static const WCHAR glu32W[] = {'g','l','u','3','2','.','d','l','l',0};
    static int already_loaded;
    static HMODULE module;

    if (already_loaded) return module;
    already_loaded = 1;

    TRACE("Trying to load GLU library\n");
    module = LoadLibraryW( glu32W );
    if (!module)
    {
        WARN("Failed to load glu32\n");
        return NULL;
    }
#define LOAD_FUNCPTR(f) p##f = (void *)GetProcAddress( module, #f )
    LOAD_FUNCPTR(gluNewTess);
    LOAD_FUNCPTR(gluDeleteTess);
    LOAD_FUNCPTR(gluTessBeginContour);
    LOAD_FUNCPTR(gluTessNormal);
    LOAD_FUNCPTR(gluTessBeginPolygon);
    LOAD_FUNCPTR(gluTessCallback);
    LOAD_FUNCPTR(gluTessEndContour);
    LOAD_FUNCPTR(gluTessEndPolygon);
    LOAD_FUNCPTR(gluTessVertex);
#undef LOAD_FUNCPTR
    return module;
}