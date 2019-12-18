#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mods ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ dvb_str_map_t ;

/* Variables and functions */
#define  APSK_16 140 
#define  APSK_32 139 
#define  DQPSK 138 
#define  PSK_8 137 
#define  QAM_128 136 
#define  QAM_16 135 
#define  QAM_256 134 
#define  QAM_32 133 
#define  QAM_64 132 
#define  QAM_AUTO 131 
#define  QPSK 130 
#define  VSB_16 129 
#define  VSB_8 128 
 int dvb_parse_str (char const*,TYPE_1__ const*,int,int) ; 

__attribute__((used)) static int dvb_parse_modulation (const char *str, int def)
{
    static const dvb_str_map_t mods[] =
    {
        { "128QAM",  QAM_128  },
        { "16APSK", APSK_16   },
        { "16QAM",   QAM_16   },
        { "16VSB",   VSB_16   },
        { "256QAM",  QAM_256  },
        { "32APSK", APSK_32   },
        { "32QAM",   QAM_32   },
        { "64QAM",   QAM_64   },
        { "8PSK",    PSK_8    },
        { "8VSB",    VSB_8    },
        { "DQPSK", DQPSK      },
        { "QAM",     QAM_AUTO },
        { "QPSK",   QPSK      },
    };
    return dvb_parse_str (str, mods, sizeof (mods) / sizeof (*mods), def);
}