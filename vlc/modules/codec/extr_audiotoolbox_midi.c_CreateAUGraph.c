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
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  AudioUnit ;
typedef  int /*<<< orphan*/  AUNode ;
typedef  int /*<<< orphan*/  AUGraph ;

/* Variables and functions */
 int /*<<< orphan*/  AUGraphConnectNodeInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUGraphNodeInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUGraphOpen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddAppleAUNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewAUGraph (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bailout ; 
 int /*<<< orphan*/  kAudioUnitSubType_DLSSynth ; 
 int /*<<< orphan*/  kAudioUnitSubType_GenericOutput ; 
 int /*<<< orphan*/  kAudioUnitSubType_MIDISynth ; 
 int /*<<< orphan*/  kAudioUnitSubType_PeakLimiter ; 
 int /*<<< orphan*/  kAudioUnitType_Effect ; 
 int /*<<< orphan*/  kAudioUnitType_MusicDevice ; 
 int /*<<< orphan*/  kAudioUnitType_Output ; 
 int /*<<< orphan*/  on_err_goto (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSStatus CreateAUGraph(AUGraph *outGraph, AudioUnit *outSynth, AudioUnit *outOut)
{
    OSStatus res;

    // AudioUnit nodes
    AUNode synthNode, limiterNode, outNode;

    // Create the Graph to which we will add our nodes
    on_err_goto(res = NewAUGraph(outGraph), bailout);

    // Create/add the MIDI synthesizer node (DLS Synth)
#if TARGET_OS_IPHONE
    // On iOS/tvOS use MIDISynth, DLSSynth does not exist there
    on_err_goto(res = AddAppleAUNode(*outGraph,
                                     kAudioUnitType_MusicDevice,
                                     kAudioUnitSubType_MIDISynth,
                                     &synthNode), bailout);
#else
    // Prefer DLSSynth on macOS, as it has a better default behavior
    on_err_goto(res = AddAppleAUNode(*outGraph,
                                     kAudioUnitType_MusicDevice,
                                     kAudioUnitSubType_DLSSynth,
                                     &synthNode), bailout);
#endif

    // Create/add the peak limiter node
    on_err_goto(res = AddAppleAUNode(*outGraph,
                                     kAudioUnitType_Effect,
                                     kAudioUnitSubType_PeakLimiter,
                                     &limiterNode), bailout);

    // Create/add the output node (GenericOutput)
    on_err_goto(res = AddAppleAUNode(*outGraph,
                                     kAudioUnitType_Output,
                                     kAudioUnitSubType_GenericOutput,
                                     &outNode), bailout);

    // Open the Graph, this opens the units that belong to the graph
    // so that we can connect them
    on_err_goto(res = AUGraphOpen(*outGraph), bailout);

    // Connect the synthesizer node to the limiter
    on_err_goto(res = AUGraphConnectNodeInput(*outGraph, synthNode, 0, limiterNode, 0), bailout);
    // Connect the limiter node to the output
    on_err_goto(res = AUGraphConnectNodeInput(*outGraph, limiterNode, 0, outNode, 0), bailout);

    // Get reference to the synthesizer node
    on_err_goto(res = AUGraphNodeInfo(*outGraph, synthNode, 0, outSynth), bailout);
    // Get reference to the output node
    on_err_goto(res = AUGraphNodeInfo(*outGraph, outNode, 0, outOut), bailout);

bailout:
    return res;
}