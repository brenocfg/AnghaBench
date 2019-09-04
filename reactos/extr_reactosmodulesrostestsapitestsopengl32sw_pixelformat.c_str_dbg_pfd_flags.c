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
typedef  int UINT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_BITMAP ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_GENERIC_ACCELERATED ; 
 int PFD_GENERIC_FORMAT ; 
 int PFD_NEED_PALETTE ; 
 int PFD_NEED_SYSTEM_PALETTE ; 
 int PFD_STEREO ; 
 int PFD_SUPPORT_COMPOSITION ; 
 int PFD_SUPPORT_GDI ; 
 int PFD_SUPPORT_OPENGL ; 
 int PFD_SWAP_COPY ; 
 int PFD_SWAP_EXCHANGE ; 
 int PFD_SWAP_LAYER_BUFFERS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char* str_dbg_pfd_flags(DWORD flags)
{
    static char buffer[1000];
    static char *p = buffer;
    char* ret;
    
    BOOL first = TRUE;

    if (p > &buffer[800])
        p = buffer;
    
    *p = 0;

#define FLAGS_TO_STR(__x__)                 \
    do {                                    \
        if (flags & __x__)                  \
        {                                   \
            if (!first) strcat(p, " | ");   \
            strcat(p, #__x__);              \
            first = FALSE;                  \
            flags &= ~((DWORD)__x__);       \
        }                                   \
    } while(0)

    FLAGS_TO_STR(PFD_DOUBLEBUFFER);
    FLAGS_TO_STR(PFD_STEREO);
    FLAGS_TO_STR(PFD_DRAW_TO_WINDOW);
    FLAGS_TO_STR(PFD_DRAW_TO_BITMAP);
    FLAGS_TO_STR(PFD_SUPPORT_GDI);
    FLAGS_TO_STR(PFD_SUPPORT_OPENGL);
    FLAGS_TO_STR(PFD_GENERIC_FORMAT);
    FLAGS_TO_STR(PFD_NEED_PALETTE);
    FLAGS_TO_STR(PFD_NEED_SYSTEM_PALETTE);
    FLAGS_TO_STR(PFD_SWAP_EXCHANGE);
    FLAGS_TO_STR(PFD_SWAP_COPY);
    FLAGS_TO_STR(PFD_SWAP_LAYER_BUFFERS);
    FLAGS_TO_STR(PFD_GENERIC_ACCELERATED);
    FLAGS_TO_STR(PFD_SUPPORT_COMPOSITION);
#undef FLAGS_TO_STR

    if (flags)
    {
        char tmp[16];
        sprintf(tmp, " | 0x%08x", (UINT)flags);
        strcat(p, tmp);
    }
    
    ret = p;
    
    p += strlen(p) + 1;

    return ret;
}