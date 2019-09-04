#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  received_reo4 ;
typedef  int /*<<< orphan*/  received_reo3 ;
typedef  int /*<<< orphan*/  received_reo2 ;
typedef  int /*<<< orphan*/  received_reo1 ;
struct TYPE_6__ {int cbStruct; int cp; int /*<<< orphan*/ * polesite; } ;
typedef  TYPE_1__ REOBJECT ;
typedef  int LPARAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  IOleClientSite ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REOBJECT_STRUCT (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 int IRichEditOle_GetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IRichEditOle_GetObject (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int IRichEditOle_GetObjectCount (int /*<<< orphan*/ *) ; 
 int IRichEditOle_InsertObject (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  REO_CP_SELECTION ; 
 int /*<<< orphan*/  REO_GETOBJ_ALL_INTERFACES ; 
 int /*<<< orphan*/  REO_GETOBJ_NO_INTERFACES ; 
 int /*<<< orphan*/  REO_GETOBJ_POLESITE ; 
 int /*<<< orphan*/  REO_GETOBJ_PSTG ; 
 int REO_IOB_USE_CP ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_reobject_struct (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_InsertObject(void)
{
  static CHAR test_text1[] = "abcdefg";
  IRichEditOle *reole = NULL;
  ITextDocument *doc = NULL;
  IOleClientSite *clientsite;
  REOBJECT reo1, reo2, reo3, received_reo1, received_reo2, received_reo3, received_reo4;
  HRESULT hr;
  HWND hwnd;
  LONG count;

  create_interfaces(&hwnd, &reole, &doc, NULL);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);

  hr = IRichEditOle_InsertObject(reole, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  /* insert object1 in (0, 1)*/
  SendMessageA(hwnd, EM_SETSEL, 0, 1);
  hr = IRichEditOle_GetClientSite(reole, &clientsite);
  ok(hr == S_OK, "IRichEditOle_GetClientSite failed: 0x%08x\n", hr);
  fill_reobject_struct(&reo1, REO_CP_SELECTION, NULL, NULL, clientsite, 10, 10, DVASPECT_CONTENT, 0, 1);
  hr = IRichEditOle_InsertObject(reole, &reo1);
  ok(hr == S_OK, "IRichEditOle_InsertObject failed: 0x%08x\n", hr);
  count = IRichEditOle_GetObjectCount(reole);
  ok(count == 1, "got wrong object count: %d\n", count);
  IOleClientSite_Release(clientsite);

  /* insert object2 in (2, 3)*/
  SendMessageA(hwnd, EM_SETSEL, 2, 3);
  hr = IRichEditOle_GetClientSite(reole, &clientsite);
  ok(hr == S_OK, "IRichEditOle_GetClientSite failed: 0x%08x\n", hr);
  fill_reobject_struct(&reo2, REO_CP_SELECTION, NULL, NULL, clientsite, 10, 10, DVASPECT_CONTENT, 0, 2);
  hr = IRichEditOle_InsertObject(reole, &reo2);
  ok(hr == S_OK, "IRichEditOle_InsertObject failed: 0x%08x\n", hr);
  count = IRichEditOle_GetObjectCount(reole);
  ok(count == 2, "got wrong object count: %d\n", count);
  IOleClientSite_Release(clientsite);

  /* insert object3 in (1, 2)*/
  SendMessageA(hwnd, EM_SETSEL, 1, 2);
  hr = IRichEditOle_GetClientSite(reole, &clientsite);
  ok(hr == S_OK, "IRichEditOle_GetClientSite failed: 0x%08x\n", hr);
  fill_reobject_struct(&reo3, REO_CP_SELECTION, NULL, NULL, clientsite, 10, 10, DVASPECT_CONTENT, 0, 3);
  hr = IRichEditOle_InsertObject(reole, &reo3);
  ok(hr == S_OK, "IRichEditOle_InsertObject failed: 0x%08x\n", hr);
  count = IRichEditOle_GetObjectCount(reole);
  ok(count == 3, "got wrong object count: %d\n", count);
  IOleClientSite_Release(clientsite);

  /* tests below show that order of rebject (from 0 to 2) is: reo1,reo3,reo2 */
  received_reo1.cbStruct = sizeof(received_reo1);
  hr = IRichEditOle_GetObject(reole, 0, &received_reo1, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo1, NULL, NULL, reo1.polesite, 1);

  received_reo2.cbStruct = sizeof(received_reo2);
  hr = IRichEditOle_GetObject(reole, 1, &received_reo2, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo2, NULL, NULL, reo3.polesite, 3);

  received_reo3.cbStruct = sizeof(received_reo3);
  hr = IRichEditOle_GetObject(reole, 2, &received_reo3, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo3, NULL, NULL, reo2.polesite, 2);

  hr = IRichEditOle_GetObject(reole, 2, NULL, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == E_INVALIDARG, "IRichEditOle_GetObject should fail: 0x%08x\n", hr);

  received_reo4.cbStruct = 0;
  hr = IRichEditOle_GetObject(reole, 2, &received_reo4, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == E_INVALIDARG, "IRichEditOle_GetObject should fail: 0x%08x\n", hr);

  received_reo4.cbStruct = sizeof(received_reo4);
  hr = IRichEditOle_GetObject(reole, 2, &received_reo4, REO_GETOBJ_PSTG);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, NULL, 2);

  hr = IRichEditOle_GetObject(reole, 2, &received_reo4, REO_GETOBJ_POLESITE);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, reo2.polesite, 2);

  hr = IRichEditOle_GetObject(reole, 4, &received_reo4, REO_GETOBJ_POLESITE);
  ok(hr == E_INVALIDARG, "IRichEditOle_GetObject should fail: 0x%08x\n", hr);

  hr = IRichEditOle_GetObject(reole, 1024, &received_reo4, REO_GETOBJ_POLESITE);
  ok(hr == E_INVALIDARG, "IRichEditOle_GetObject should fail: 0x%08x\n", hr);

  /* received_reo4 will be zeroed before be used */
  hr = IRichEditOle_GetObject(reole, 2, &received_reo4, REO_GETOBJ_NO_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, NULL, 2);

  received_reo4.cbStruct = sizeof(received_reo4);
  received_reo4.cp = 0;
  hr = IRichEditOle_GetObject(reole, REO_IOB_USE_CP, &received_reo4, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, reo1.polesite, 1);

  received_reo4.cbStruct = sizeof(received_reo4);
  received_reo4.cp = 1;
  hr = IRichEditOle_GetObject(reole, REO_IOB_USE_CP, &received_reo4, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, reo3.polesite, 3);

  received_reo4.cbStruct = sizeof(received_reo4);
  received_reo4.cp = 2;
  hr = IRichEditOle_GetObject(reole, REO_IOB_USE_CP, &received_reo4, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == S_OK, "IRichEditOle_GetObject failed: 0x%08x\n", hr);
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, reo2.polesite, 2);

  received_reo4.cbStruct = sizeof(received_reo4);
  received_reo4.cp = 4;
  hr = IRichEditOle_GetObject(reole, REO_IOB_USE_CP, &received_reo4, REO_GETOBJ_ALL_INTERFACES);
  ok(hr == E_INVALIDARG, "IRichEditOle_GetObject should fail: 0x%08x\n", hr);
  /* received_reo4 didn't be zeroed in E_INVALIDARG case */
  CHECK_REOBJECT_STRUCT(received_reo4, NULL, NULL, reo2.polesite, 2);

  release_interfaces(&hwnd, &reole, &doc, NULL);
}