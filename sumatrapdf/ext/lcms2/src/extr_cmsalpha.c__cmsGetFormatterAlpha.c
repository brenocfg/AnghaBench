#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsFormatterAlphaFn ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  const member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int FormatterPos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  copy16 160 
#define  copy32 159 
#define  copy64 158 
#define  copy8 157 
#define  from16SEto8 156 
#define  from16SEtoDBL 155 
#define  from16SEtoFLT 154 
#define  from16SEtoHLF 153 
#define  from16to16 152 
#define  from16to8 151 
#define  from16toDBL 150 
#define  from16toFLT 149 
#define  from16toHLF 148 
#define  from8to16 147 
#define  from8to16SE 146 
#define  from8toDBL 145 
#define  from8toFLT 144 
#define  from8toHLF 143 
#define  fromDBLto16 142 
#define  fromDBLto16SE 141 
#define  fromDBLto8 140 
#define  fromDBLtoFLT 139 
#define  fromDBLtoHLF 138 
#define  fromFLTto16 137 
#define  fromFLTto16SE 136 
#define  fromFLTto8 135 
#define  fromFLTtoDBL 134 
#define  fromFLTtoHLF 133 
#define  fromHLFto16 132 
#define  fromHLFto16SE 131 
#define  fromHLFto8 130 
#define  fromHLFtoDBL 129 
#define  fromHLFtoFLT 128 

__attribute__((used)) static
cmsFormatterAlphaFn _cmsGetFormatterAlpha(cmsContext id, cmsUInt32Number in, cmsUInt32Number out)
{
static cmsFormatterAlphaFn FormattersAlpha[6][6] = {

       /* from 8 */  { copy8,       from8to16,   from8to16SE,   from8toHLF,   from8toFLT,    from8toDBL    },
       /* from 16*/  { from16to8,   copy16,      from16to16,    from16toHLF,  from16toFLT,   from16toDBL   },
       /* from 16SE*/{ from16SEto8, from16to16,  copy16,        from16SEtoHLF,from16SEtoFLT, from16SEtoDBL },
       /* from HLF*/ { fromHLFto8,  fromHLFto16, fromHLFto16SE, copy16,       fromHLFtoFLT,  fromHLFtoDBL  },
       /* from FLT*/ { fromFLTto8,  fromFLTto16, fromFLTto16SE, fromFLTtoHLF, copy32,        fromFLTtoDBL  },
       /* from DBL*/ { fromDBLto8,  fromDBLto16, fromDBLto16SE, fromDBLtoHLF, fromDBLtoFLT,  copy64 }};

        int in_n  = FormatterPos(in);
        int out_n = FormatterPos(out);

        if (in_n < 0 || out_n < 0 || in_n > 4 || out_n > 4) {

               cmsSignalError(id, cmsERROR_UNKNOWN_EXTENSION, "Unrecognized alpha channel width");
               return NULL;
        }

        return FormattersAlpha[in_n][out_n];
}