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
typedef  int uint_fast32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FLAGS ; 
 int VLC_CPU_3dNOW ; 
 int VLC_CPU_ALTIVEC ; 
 int VLC_CPU_ARM_NEON ; 
 int VLC_CPU_ARM_SVE ; 
 int VLC_CPU_ARMv6 ; 
 int VLC_CPU_AVX ; 
 int VLC_CPU_AVX2 ; 
 int VLC_CPU_FMA4 ; 
 int VLC_CPU_MMX ; 
 int VLC_CPU_MMXEXT ; 
 int VLC_CPU_SSE ; 
 int VLC_CPU_SSE2 ; 
 int VLC_CPU_SSE3 ; 
 int VLC_CPU_SSE4A ; 
 int VLC_CPU_SSE4_1 ; 
 int VLC_CPU_SSE4_2 ; 
 int VLC_CPU_SSSE3 ; 
 int VLC_CPU_XOP ; 
 int cpu_flags ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void vlc_CPU_init (void)
{
    FILE *info = fopen ("/proc/cpuinfo", "rte");
    if (info == NULL)
        return;

    char *line = NULL;
    size_t linelen = 0;
    uint_fast32_t all_caps = 0xFFFFFFFF;

    while (getline (&line, &linelen, info) != -1)
    {
        char *p = line, *cap;
        uint_fast32_t core_caps = 0;

#if defined (__arm__)
        unsigned ver;
        if (sscanf (line, "Processor\t: ARMv%u", &ver) >= 1 && ver >= 6)
            core_caps |= VLC_CPU_ARMv6;
#endif
        if (strncmp (line, CPU_FLAGS, strlen (CPU_FLAGS)))
            continue;

        while ((cap = strsep (&p, " ")) != NULL)
        {
#if defined (__arm__) || defined (__aarch64__)
            if (!strcmp (cap, "neon"))
                core_caps |= VLC_CPU_ARM_NEON;
# if defined (__aarch64__)
            if (!strcmp (cap, "sve"))
                core_caps |= VLC_CPU_ARM_SVE;
# endif

#elif defined (__i386__) || defined (__x86_64__)
            if (!strcmp (cap, "mmx"))
                core_caps |= VLC_CPU_MMX;
            if (!strcmp (cap, "sse"))
                core_caps |= VLC_CPU_SSE | VLC_CPU_MMXEXT;
            if (!strcmp (cap, "mmxext"))
                core_caps |= VLC_CPU_MMXEXT;
            if (!strcmp (cap, "sse2"))
                core_caps |= VLC_CPU_SSE2;
            if (!strcmp (cap, "pni"))
                core_caps |= VLC_CPU_SSE3;
            if (!strcmp (cap, "ssse3"))
                core_caps |= VLC_CPU_SSSE3;
            if (!strcmp (cap, "sse4_1"))
                core_caps |= VLC_CPU_SSE4_1;
            if (!strcmp (cap, "sse4_2"))
                core_caps |= VLC_CPU_SSE4_2;
            if (!strcmp (cap, "sse4a"))
                core_caps |= VLC_CPU_SSE4A;
            if (!strcmp (cap, "avx"))
                core_caps |= VLC_CPU_AVX;
            if (!strcmp (cap, "avx2"))
                core_caps |= VLC_CPU_AVX2;
            if (!strcmp (cap, "3dnow"))
                core_caps |= VLC_CPU_3dNOW;
            if (!strcmp (cap, "xop"))
                core_caps |= VLC_CPU_XOP;
            if (!strcmp (cap, "fma4"))
                core_caps |= VLC_CPU_FMA4;

#elif defined (__powerpc__) || defined (__powerpc64__)
            if (!strcmp (cap, "altivec supported"))
                core_caps |= VLC_CPU_ALTIVEC;
#endif
        }

        /* Take the intersection of capabilities of each processor */
        all_caps &= core_caps;
    }
    fclose (info);
    free (line);

    if (all_caps == 0xFFFFFFFF) /* Error parsing of cpuinfo? */
        all_caps = 0; /* Do not assume any capability! */

    cpu_flags = all_caps;
}