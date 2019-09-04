#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct detail_data {TYPE_1__* pCertViewInfo; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * (* prop_to_value ) (int /*<<< orphan*/ *,size_t) ;scalar_t__ prop_is_string; int /*<<< orphan*/  prop; } ;
struct TYPE_4__ {int /*<<< orphan*/  pCertContext; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ CertGetCertificateContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_string_id_and_value_to_list (int /*<<< orphan*/ ,struct detail_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* prop_id_map ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void add_properties(HWND hwnd, struct detail_data *data)
{
    DWORD i;
    PCCERT_CONTEXT cert = data->pCertViewInfo->pCertContext;

    for (i = 0; i < ARRAY_SIZE(prop_id_map); i++)
    {
        DWORD cb;

        if (CertGetCertificateContextProperty(cert, prop_id_map[i].prop, NULL,
         &cb))
        {
            BYTE *pb;
            WCHAR *val = NULL;

            /* FIXME: MS adds a separate value for the signature hash
             * algorithm.
             */
            pb = HeapAlloc(GetProcessHeap(), 0, cb);
            if (pb)
            {
                if (CertGetCertificateContextProperty(cert,
                 prop_id_map[i].prop, pb, &cb))
                {
                    if (prop_id_map[i].prop_is_string)
                    {
                        val = (LPWSTR)pb;
                        /* Don't double-free pb */
                        pb = NULL;
                    }
                    else
                        val = prop_id_map[i].prop_to_value(pb, cb);
                }
                HeapFree(GetProcessHeap(), 0, pb);
            }
            add_string_id_and_value_to_list(hwnd, data, prop_id_map[i].id, val,
             NULL, NULL);
        }
    }
}