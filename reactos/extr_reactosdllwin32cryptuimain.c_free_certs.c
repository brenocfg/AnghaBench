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
struct TYPE_2__ {int iItem; scalar_t__ lParam; scalar_t__ iSubItem; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  TYPE_1__ LVITEMW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVIF_PARAM ; 
 int /*<<< orphan*/  LVM_GETITEMCOUNT ; 
 int /*<<< orphan*/  LVM_GETITEMW ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_certs(HWND lv)
{
    LVITEMW item;
    int items = SendMessageW(lv, LVM_GETITEMCOUNT, 0, 0), i;

    for (i = 0; i < items; i++)
    {
        item.mask = LVIF_PARAM;
        item.iItem = i;
        item.iSubItem = 0;
        SendMessageW(lv, LVM_GETITEMW, 0, (LPARAM)&item);
        CertFreeCertificateContext((PCCERT_CONTEXT)item.lParam);
    }
}