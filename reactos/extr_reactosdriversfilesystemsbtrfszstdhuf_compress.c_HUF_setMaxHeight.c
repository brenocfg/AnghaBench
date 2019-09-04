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
typedef  int /*<<< orphan*/  rankLast ;
struct TYPE_3__ {size_t nbBits; size_t count; } ;
typedef  TYPE_1__ nodeElt ;
typedef  size_t U32 ;
typedef  size_t const BYTE ;

/* Variables and functions */
 size_t BIT_highbit32 (int) ; 
 int HUF_TABLELOG_MAX ; 
 int /*<<< orphan*/  memset (size_t*,int,int) ; 

__attribute__((used)) static U32 HUF_setMaxHeight(nodeElt* huffNode, U32 lastNonNull, U32 maxNbBits)
{
    const U32 largestBits = huffNode[lastNonNull].nbBits;
    if (largestBits <= maxNbBits) return largestBits;   /* early exit : no elt > maxNbBits */

    /* there are several too large elements (at least >= 2) */
    {   int totalCost = 0;
        const U32 baseCost = 1 << (largestBits - maxNbBits);
        U32 n = lastNonNull;

        while (huffNode[n].nbBits > maxNbBits) {
            totalCost += baseCost - (1 << (largestBits - huffNode[n].nbBits));
            huffNode[n].nbBits = (BYTE)maxNbBits;
            n --;
        }  /* n stops at huffNode[n].nbBits <= maxNbBits */
        while (huffNode[n].nbBits == maxNbBits) n--;   /* n end at index of smallest symbol using < maxNbBits */

        /* renorm totalCost */
        totalCost >>= (largestBits - maxNbBits);  /* note : totalCost is necessarily a multiple of baseCost */

        /* repay normalized cost */
        {   U32 const noSymbol = 0xF0F0F0F0;
            U32 rankLast[HUF_TABLELOG_MAX+2];
            int pos;

            /* Get pos of last (smallest) symbol per rank */
            memset(rankLast, 0xF0, sizeof(rankLast));
            {   U32 currentNbBits = maxNbBits;
                for (pos=n ; pos >= 0; pos--) {
                    if (huffNode[pos].nbBits >= currentNbBits) continue;
                    currentNbBits = huffNode[pos].nbBits;   /* < maxNbBits */
                    rankLast[maxNbBits-currentNbBits] = pos;
            }   }

            while (totalCost > 0) {
                U32 nBitsToDecrease = BIT_highbit32(totalCost) + 1;
                for ( ; nBitsToDecrease > 1; nBitsToDecrease--) {
                    U32 highPos = rankLast[nBitsToDecrease];
                    U32 lowPos = rankLast[nBitsToDecrease-1];
                    if (highPos == noSymbol) continue;
                    if (lowPos == noSymbol) break;
                    {   U32 const highTotal = huffNode[highPos].count;
                        U32 const lowTotal = 2 * huffNode[lowPos].count;
                        if (highTotal <= lowTotal) break;
                }   }
                /* only triggered when no more rank 1 symbol left => find closest one (note : there is necessarily at least one !) */
                /* HUF_MAX_TABLELOG test just to please gcc 5+; but it should not be necessary */
                while ((nBitsToDecrease<=HUF_TABLELOG_MAX) && (rankLast[nBitsToDecrease] == noSymbol))
                    nBitsToDecrease ++;
                totalCost -= 1 << (nBitsToDecrease-1);
                if (rankLast[nBitsToDecrease-1] == noSymbol)
                    rankLast[nBitsToDecrease-1] = rankLast[nBitsToDecrease];   /* this rank is no longer empty */
                huffNode[rankLast[nBitsToDecrease]].nbBits ++;
                if (rankLast[nBitsToDecrease] == 0)    /* special case, reached largest symbol */
                    rankLast[nBitsToDecrease] = noSymbol;
                else {
                    rankLast[nBitsToDecrease]--;
                    if (huffNode[rankLast[nBitsToDecrease]].nbBits != maxNbBits-nBitsToDecrease)
                        rankLast[nBitsToDecrease] = noSymbol;   /* this rank is now empty */
            }   }   /* while (totalCost > 0) */

            while (totalCost < 0) {  /* Sometimes, cost correction overshoot */
                if (rankLast[1] == noSymbol) {  /* special case : no rank 1 symbol (using maxNbBits-1); let's create one from largest rank 0 (using maxNbBits) */
                    while (huffNode[n].nbBits == maxNbBits) n--;
                    huffNode[n+1].nbBits--;
                    rankLast[1] = n+1;
                    totalCost++;
                    continue;
                }
                huffNode[ rankLast[1] + 1 ].nbBits--;
                rankLast[1]++;
                totalCost ++;
    }   }   }   /* there are several too large elements (at least >= 2) */

    return maxNbBits;
}