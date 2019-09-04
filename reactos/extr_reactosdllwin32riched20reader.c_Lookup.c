#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; TYPE_2__** value; } ;
struct TYPE_7__ {int rtfKHash; int /*<<< orphan*/  rtfKMinor; int /*<<< orphan*/  rtfKMajor; int /*<<< orphan*/  rtfKStr; } ;
struct TYPE_6__ {int /*<<< orphan*/  rtfClass; int /*<<< orphan*/  rtfMinor; int /*<<< orphan*/  rtfMajor; } ;
typedef  TYPE_1__ RTF_Info ;
typedef  TYPE_2__ RTFKey ;
typedef  TYPE_3__ RTFHashTableEntry ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int Hash (char*) ; 
 int /*<<< orphan*/  rtfControl ; 
 TYPE_3__* rtfHashTable ; 
 int /*<<< orphan*/  rtfKey ; 
 int /*<<< orphan*/  rtfUnknown ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Lookup(RTF_Info *info, char *s)
{
	RTFKey	*rp;
	int	hash;
        RTFHashTableEntry *entry;
        int i;

	++s;			/* skip over the leading \ character */
	hash = Hash (s);
        entry = &rtfHashTable[hash % (ARRAY_SIZE(rtfKey) * 2)];
	for (i = 0; i < entry->count; i++)
	{
                rp = entry->value[i];
		if (hash == rp->rtfKHash && strcmp (s, rp->rtfKStr) == 0)
		{
			info->rtfClass = rtfControl;
			info->rtfMajor = rp->rtfKMajor;
			info->rtfMinor = rp->rtfKMinor;
			return;
		}
	}
	info->rtfClass = rtfUnknown;
}