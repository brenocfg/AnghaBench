#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  tStop; int /*<<< orphan*/  tStart; } ;
typedef  TYPE_1__ newsegmentargs ;
typedef  TYPE_1__* LPVOID ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IPin_NewSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT deliver_newsegment(IPin *pin, LPVOID data)
{
    newsegmentargs *args = data;
    return IPin_NewSegment(pin, args->tStart, args->tStop, args->rate);
}