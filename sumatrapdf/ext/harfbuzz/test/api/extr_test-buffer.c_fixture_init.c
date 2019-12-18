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
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  gconstpointer ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ fixture_t ;

/* Variables and functions */
#define  BUFFER_EMPTY 132 
#define  BUFFER_ONE_BY_ONE 131 
#define  BUFFER_UTF16 130 
#define  BUFFER_UTF32 129 
#define  BUFFER_UTF8 128 
 int GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_N_ELEMENTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  hb_buffer_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hb_buffer_add_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_add_utf32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_add_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_buffer_create () ; 
 int /*<<< orphan*/ * utf16 ; 
 int /*<<< orphan*/ * utf32 ; 
 int /*<<< orphan*/ * utf8 ; 

__attribute__((used)) static void
fixture_init (fixture_t *fixture, gconstpointer user_data)
{
  hb_buffer_t *b;
  unsigned int i;

  b = fixture->buffer = hb_buffer_create ();

  switch (GPOINTER_TO_INT (user_data))
  {
    case BUFFER_EMPTY:
      break;

    case BUFFER_ONE_BY_ONE:
      for (i = 1; i < G_N_ELEMENTS (utf32) - 1; i++)
	hb_buffer_add (b, utf32[i], i);
      break;

    case BUFFER_UTF32:
      hb_buffer_add_utf32 (b, utf32, G_N_ELEMENTS (utf32), 1, G_N_ELEMENTS (utf32) - 2);
      break;

    case BUFFER_UTF16:
      hb_buffer_add_utf16 (b, utf16, G_N_ELEMENTS (utf16), 1, G_N_ELEMENTS (utf16) - 2);
      break;

    case BUFFER_UTF8:
      hb_buffer_add_utf8  (b, utf8,  G_N_ELEMENTS (utf8),  1, G_N_ELEMENTS (utf8)  - 2);
      break;

    default:
      g_assert_not_reached ();
  }
}