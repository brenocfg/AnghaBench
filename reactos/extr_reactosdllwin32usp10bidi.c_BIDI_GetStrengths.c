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
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SCRIPT_CONTROL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  AL 145 
#define  AN 144 
#define  B 143 
 int BIDI_NEUTRAL ; 
 int BIDI_STRONG ; 
 int BIDI_WEAK ; 
#define  BN 142 
#define  CS 141 
#define  EN 140 
#define  ES 139 
#define  ET 138 
#define  L 137 
#define  LRE 136 
#define  LRO 135 
#define  ON 134 
#define  PDF 133 
#define  R 132 
#define  RLE 131 
#define  RLO 130 
#define  S 129 
 int /*<<< orphan*/  TRUE ; 
#define  WS 128 
 int /*<<< orphan*/  classify (int /*<<< orphan*/  const*,int*,unsigned int,int /*<<< orphan*/  const*) ; 

BOOL BIDI_GetStrengths(const WCHAR *string, unsigned int count, const SCRIPT_CONTROL *c, WORD *strength)
{
    unsigned int i;

    classify(string, strength, count, c);
    for (i = 0; i < count; i++)
    {
        switch (strength[i])
        {
            case L:
            case LRE:
            case LRO:
            case R:
            case AL:
            case RLE:
            case RLO:
                strength[i] = BIDI_STRONG;
                break;
            case PDF:
            case EN:
            case ES:
            case ET:
            case AN:
            case CS:
            case BN:
                strength[i] = BIDI_WEAK;
                break;
            case B:
            case S:
            case WS:
            case ON:
            default: /* Neutrals and NSM */
                strength[i] = BIDI_NEUTRAL;
        }
    }
    return TRUE;
}