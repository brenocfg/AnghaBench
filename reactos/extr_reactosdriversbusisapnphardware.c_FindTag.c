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
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISAPNP_IS_SMALL_TAG (scalar_t__) ; 
 scalar_t__ ISAPNP_LARGE_TAG_NAME (scalar_t__) ; 
 scalar_t__ ISAPNP_SMALL_TAG_LEN (scalar_t__) ; 
 scalar_t__ ISAPNP_SMALL_TAG_NAME (scalar_t__) ; 
 scalar_t__ ISAPNP_TAG_END ; 
 int /*<<< orphan*/  Peek (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int PeekByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOLEAN
FindTag(PUCHAR ReadDataPort, USHORT WantedTag, PVOID Buffer, ULONG Length)
{
  USHORT Tag, TagLen;

  do
  {
    Tag = PeekByte(ReadDataPort);
    if (ISAPNP_IS_SMALL_TAG(Tag))
    {
      TagLen = ISAPNP_SMALL_TAG_LEN(Tag);
      Tag = ISAPNP_SMALL_TAG_NAME(Tag);
    }
    else
    {
      TagLen = PeekByte(ReadDataPort) + (PeekByte(ReadDataPort) << 8);
      Tag = ISAPNP_LARGE_TAG_NAME(Tag);
    }

    if (Tag == WantedTag)
    {
      if (Length > TagLen)
          Length = TagLen;

      Peek(ReadDataPort, Buffer, Length);

      return TRUE;
    }
    else
    {
      Peek(ReadDataPort, NULL, Length);
    }
  } while (Tag != ISAPNP_TAG_END);

  return FALSE;
}