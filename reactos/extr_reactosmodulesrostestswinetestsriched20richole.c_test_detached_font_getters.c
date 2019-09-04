#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  ITextFont ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ ITextFont_GetBold (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetForeColor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetItalic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetLanguageID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetSize (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ ITextFont_GetStrikeThrough (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetSubscript (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetSuperscript (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetUnderline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_detached_font_getters(ITextFont *font, BOOL duplicate)
{
  HRESULT hr, hrexp = duplicate ? S_OK : CO_E_RELEASED;
  LONG value;
  float size;
  BSTR str;

  hr = ITextFont_GetBold(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetBold(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetForeColor(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetForeColor(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetItalic(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetItalic(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetLanguageID(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetLanguageID(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetName(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetName(font, &str);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetSize(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetSize(font, &size);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetStrikeThrough(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetStrikeThrough(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetSubscript(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetSubscript(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetSuperscript(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetSuperscript(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);

  hr = ITextFont_GetUnderline(font, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextFont_GetUnderline(font, &value);
  ok(hr == hrexp, "got 0x%08x\n", hr);
}