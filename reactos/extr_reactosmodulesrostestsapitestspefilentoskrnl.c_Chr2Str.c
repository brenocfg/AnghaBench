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
typedef  int DWORD ;

/* Variables and functions */
 int IMAGE_SCN_ALIGN_16BYTES ; 
 int IMAGE_SCN_ALIGN_1BYTES ; 
 int IMAGE_SCN_ALIGN_2BYTES ; 
 int IMAGE_SCN_ALIGN_32BYTES ; 
 int IMAGE_SCN_ALIGN_4BYTES ; 
 int IMAGE_SCN_ALIGN_64BYTES ; 
 int IMAGE_SCN_ALIGN_8BYTES ; 
 int IMAGE_SCN_CNT_CODE ; 
 int IMAGE_SCN_CNT_INITIALIZED_DATA ; 
 int IMAGE_SCN_CNT_UNINITIALIZED_DATA ; 
 int IMAGE_SCN_LNK_COMDAT ; 
 int IMAGE_SCN_LNK_INFO ; 
 int IMAGE_SCN_LNK_NRELOC_OVFL ; 
 int IMAGE_SCN_LNK_OTHER ; 
 int IMAGE_SCN_LNK_REMOVE ; 
 int IMAGE_SCN_MEM_16BIT ; 
 int IMAGE_SCN_MEM_DISCARDABLE ; 
 int IMAGE_SCN_MEM_EXECUTE ; 
 int IMAGE_SCN_MEM_FARDATA ; 
 int IMAGE_SCN_MEM_LOCKED ; 
 int IMAGE_SCN_MEM_NOT_CACHED ; 
 int IMAGE_SCN_MEM_NOT_PAGED ; 
 int IMAGE_SCN_MEM_PRELOAD ; 
 int IMAGE_SCN_MEM_PURGEABLE ; 
 int IMAGE_SCN_MEM_READ ; 
 int IMAGE_SCN_MEM_SHARED ; 
 int IMAGE_SCN_MEM_WRITE ; 
 int IMAGE_SCN_TYPE_NO_PAD ; 
 int /*<<< orphan*/  StringCchCatA (char*,int,char*) ; 
 int /*<<< orphan*/  StringCchPrintfA (char*,int,char*,int) ; 
 int _countof (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char* Chr2Str(DWORD value)
{
    static char buf[512];
    buf[0] = '\0';
#define IFX(x)      if( value & IMAGE_SCN_##x )\
                    {\
                        if(buf[0]) { StringCchCatA(buf, _countof(buf), "|" ); }\
                        StringCchCatA(buf, _countof(buf), #x );\
                        value &= ~(IMAGE_SCN_##x);\
                    }
    IFX(TYPE_NO_PAD);
    IFX(CNT_CODE);
    IFX(CNT_INITIALIZED_DATA);
    IFX(CNT_UNINITIALIZED_DATA);
    IFX(LNK_OTHER);
    IFX(LNK_INFO);
    IFX(LNK_REMOVE);
    IFX(LNK_COMDAT);
    //IFX(NO_DEFER_SPEC_EXC);
    //IFX(GPREL);
    IFX(MEM_FARDATA);
    IFX(MEM_PURGEABLE);
    IFX(MEM_16BIT);
    IFX(MEM_LOCKED);
    IFX(MEM_PRELOAD);
    IFX(ALIGN_1BYTES);
    IFX(ALIGN_2BYTES);
    IFX(ALIGN_4BYTES);
    IFX(ALIGN_8BYTES);
    IFX(ALIGN_16BYTES);
    IFX(ALIGN_32BYTES);
    IFX(ALIGN_64BYTES);
    //IFX(ALIGN_128BYTES);
    //IFX(ALIGN_256BYTES);
    //IFX(ALIGN_512BYTES);
    //IFX(ALIGN_1024BYTES);
    //IFX(ALIGN_2048BYTES);
    //IFX(ALIGN_4096BYTES);
    //IFX(ALIGN_8192BYTES);
    IFX(LNK_NRELOC_OVFL);
    IFX(MEM_DISCARDABLE);
    IFX(MEM_NOT_CACHED);
    IFX(MEM_NOT_PAGED);
    IFX(MEM_SHARED);
    IFX(MEM_EXECUTE);
    IFX(MEM_READ);
    IFX(MEM_WRITE);
    if( value )
    {
        StringCchPrintfA(buf + strlen(buf), _countof(buf) - strlen(buf), "|0x%x", value);
    }
    return buf;
}