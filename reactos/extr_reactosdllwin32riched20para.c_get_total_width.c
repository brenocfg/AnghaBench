#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_8__* pBuffer; } ;
struct TYPE_20__ {TYPE_6__* pLast; TYPE_7__* pFirst; } ;
struct TYPE_19__ {TYPE_2__* next; } ;
struct TYPE_12__ {TYPE_5__* next_para; int /*<<< orphan*/  nWidth; } ;
struct TYPE_15__ {TYPE_10__ para; } ;
struct TYPE_18__ {TYPE_3__ member; } ;
struct TYPE_16__ {TYPE_10__ para; } ;
struct TYPE_17__ {TYPE_4__ member; } ;
struct TYPE_13__ {TYPE_10__ para; } ;
struct TYPE_14__ {TYPE_1__ member; } ;
typedef  TYPE_9__ ME_TextEditor ;
typedef  TYPE_10__ ME_Paragraph ;

/* Variables and functions */
 int max (int,int /*<<< orphan*/ ) ; 

int get_total_width(ME_TextEditor *editor)
{
    ME_Paragraph *para;
    int total_width = 0;

    if (editor->pBuffer->pFirst && editor->pBuffer->pLast)
    {
        para = &editor->pBuffer->pFirst->next->member.para;
        while (para != &editor->pBuffer->pLast->member.para && para->next_para)
        {
            total_width = max(total_width, para->nWidth);
            para = &para->next_para->member.para;
        }
    }

    return total_width;
}