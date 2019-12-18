#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct mod   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tab ;
struct mod {char* dvb; char* vlc; } ;

/* Variables and functions */
 struct mod* bsearch (char const*,TYPE_1__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp ; 

__attribute__((used)) static const char *ParseModulation(const char *str)
{
     static const struct mod
     {
         char dvb[9];
         char vlc[7];
     } tab[] = {
         { "8VSB", "8VSB" }, { "APSK_16", "16APSK" }, { "APSK_32", "32APSK" },
         { "DQPSK", "DQPSK" }, { "PSK_8", "8PSK" }, { "QPSK", "QPSK" },
         { "QAM_128", "128QAM" }, { "QAM_16", "16QAM" },
         { "QAM_256", "256QAM" }, { "QAM_32", "32QAM" },
         { "QAM_64", "64QAM" }, { "QAM_AUTO", "QAM" },
         { "VSB_16", "16VSB" }, { "VSB_8", "8VSB" }
     };

     if( str == NULL )
         return NULL;

     const struct mod *m = bsearch(str, tab, sizeof (tab) / sizeof(tab[0]),
                                   sizeof (tab[0]), cmp);
     return (m != NULL) ? m->vlc : NULL;
}