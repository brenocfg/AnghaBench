#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  max_token; TYPE_4__* out_buf; TYPE_2__* in_buf; } ;
struct TYPE_11__ {int cBuffers; TYPE_3__* pBuffers; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pvBuffer; int /*<<< orphan*/  cbBuffer; } ;
struct TYPE_9__ {int cBuffers; TYPE_1__* pBuffers; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbBuffer; int /*<<< orphan*/ * pvBuffer; } ;
typedef  TYPE_5__ SspiData ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void communicate(SspiData *from, SspiData *to)
{
    if(from->out_buf != NULL && to->in_buf != NULL)
    {
        trace("Running communicate.\n");
        if((from->out_buf->cBuffers >= 1) && (to->in_buf->cBuffers >= 1))
        {
            if((from->out_buf->pBuffers[0].pvBuffer != NULL) && 
                    (to->in_buf->pBuffers[0].pvBuffer != NULL))
            {
                memset(to->in_buf->pBuffers[0].pvBuffer, 0, to->max_token);
                
                memcpy(to->in_buf->pBuffers[0].pvBuffer, 
                    from->out_buf->pBuffers[0].pvBuffer,
                    from->out_buf->pBuffers[0].cbBuffer);
                
                to->in_buf->pBuffers[0].cbBuffer = from->out_buf->pBuffers[0].cbBuffer;
                
                memset(from->out_buf->pBuffers[0].pvBuffer, 0, from->max_token);
            }
        }
    }
}