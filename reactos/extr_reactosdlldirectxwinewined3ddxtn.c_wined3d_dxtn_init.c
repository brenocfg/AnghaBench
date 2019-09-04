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
typedef  int /*<<< orphan*/  soname ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  TRUE ; 
 void* pfetch_2d_texel_rgba_dxt1 ; 
 void* pfetch_2d_texel_rgba_dxt3 ; 
 void* pfetch_2d_texel_rgba_dxt5 ; 
 void* ptx_compress_dxtn ; 
 int /*<<< orphan*/ * txc_dxtn_handle ; 
 int /*<<< orphan*/  wine_dlclose (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wine_dlopen (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* wine_dlsym (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL wined3d_dxtn_init(void)
{
    static const char *soname[] =
    {
#ifdef SONAME_LIBTXC_DXTN
        SONAME_LIBTXC_DXTN,
#endif
#ifdef __APPLE__
        "libtxc_dxtn.dylib",
        "libtxc_dxtn_s2tc.dylib",
#endif
        "libtxc_dxtn.so",
        "libtxc_dxtn_s2tc.so.0"
    };
    int i;

    for (i = 0; i < sizeof(soname)/sizeof(soname[0]); i++)
    {
        txc_dxtn_handle = wine_dlopen(soname[i], RTLD_NOW, NULL, 0);
        if (txc_dxtn_handle) break;
    }

    if (!txc_dxtn_handle)
    {
        FIXME("Wine cannot find the txc_dxtn library, DXTn software support unavailable.\n");
        return FALSE;
    }

    #define LOAD_FUNCPTR(f) \
        if (!(p##f = wine_dlsym(txc_dxtn_handle, #f, NULL, 0))) \
        { \
            ERR("Can't find symbol %s , DXTn software support unavailable.\n", #f); \
            goto error; \
        }

    LOAD_FUNCPTR(fetch_2d_texel_rgba_dxt1);
    LOAD_FUNCPTR(fetch_2d_texel_rgba_dxt3);
    LOAD_FUNCPTR(fetch_2d_texel_rgba_dxt5);
    LOAD_FUNCPTR(tx_compress_dxtn);

    #undef LOAD_FUNCPTR
    return TRUE;

error:
    wine_dlclose(txc_dxtn_handle, NULL, 0);
    txc_dxtn_handle = NULL;
    return FALSE;
}