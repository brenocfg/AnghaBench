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
struct TYPE_2__ {scalar_t__ encoding; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  scalar_t__ OMX_AUDIO_CODINGTYPE ;

/* Variables and functions */
 scalar_t__ OMX_AUDIO_CodingUnused ; 
 TYPE_1__* audio_encoding_param ; 

__attribute__((used)) static OMX_INDEXTYPE GetAudioParamFormatIndex(OMX_AUDIO_CODINGTYPE encoding)
{
  int i;

  for(i = 0; audio_encoding_param[i].encoding != OMX_AUDIO_CodingUnused &&
      audio_encoding_param[i].encoding != encoding; i++);

  return audio_encoding_param[i].index;
}