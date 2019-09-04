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
struct TYPE_3__ {int /*<<< orphan*/  ulCntData; int /*<<< orphan*/  abData; } ;
typedef  TYPE_1__ InterfaceData ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT create_stream_on_mip_ro(const InterfaceData *mip, IStream **stream)
{
    HGLOBAL hglobal = GlobalAlloc(0, mip->ulCntData);
    void *pv = GlobalLock(hglobal);
    memcpy(pv, mip->abData, mip->ulCntData);
    GlobalUnlock(hglobal);
    return CreateStreamOnHGlobal(hglobal, TRUE, stream);
}