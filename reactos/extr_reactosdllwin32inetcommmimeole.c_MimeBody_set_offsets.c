#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cbBodyEnd; int /*<<< orphan*/  cbBodyStart; int /*<<< orphan*/  cbHeaderStart; int /*<<< orphan*/  cbBoundaryStart; } ;
struct TYPE_5__ {TYPE_2__ body_offsets; } ;
typedef  TYPE_1__ MimeBody ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ BODYOFFSETS ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT MimeBody_set_offsets(MimeBody *body, const BODYOFFSETS *offsets)
{
    TRACE("setting offsets to %d, %d, %d, %d\n", offsets->cbBoundaryStart,
          offsets->cbHeaderStart, offsets->cbBodyStart, offsets->cbBodyEnd);

    body->body_offsets = *offsets;
    return S_OK;
}