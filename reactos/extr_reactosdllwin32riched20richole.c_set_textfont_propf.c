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
struct TYPE_3__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ textfont_prop_val ;
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
typedef  int /*<<< orphan*/  ITextFontImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  set_textfont_prop (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static inline HRESULT set_textfont_propf(ITextFontImpl *font, enum textfont_prop_id propid, FLOAT value)
{
    textfont_prop_val v;
    v.f = value;
    return set_textfont_prop(font, propid, &v);
}