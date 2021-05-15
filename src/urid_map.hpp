#pragma once
#include "lv2/core/lv2.h"
#include "lv2/atom/atom.h"
#include "lv2/midi/midi.h"
#include <cstring>

enum HostURIDs {
  kUridAtomBool,
  kUridAtomFloat,
  kUridAtomInt,
  kUridAtomBlank,
  kUridAtomObject,
  kUridAtomDouble,
  kUridAtomLong,
  kUridAtomSequence,
  kUridAtomString,
  kUridAtomProperty,
  kUridMidiEvent
};

LV2_URID urid_map_fn(LV2_URID_Map_Handle handle, const char* uri) {
  if (std::strcmp(uri, LV2_ATOM__Int) == 0) {
    return kUridAtomInt;
  }
  if (std::strcmp(uri, LV2_ATOM__Blank) == 0) {
    return kUridAtomBlank;
  }
  if (std::strcmp(uri, LV2_ATOM__Object) == 0) {
    return kUridAtomObject;
  }
  if (std::strcmp(uri, LV2_ATOM__Double) == 0) {
    return kUridAtomDouble;
  }
  if (std::strcmp(uri, LV2_ATOM__Float) == 0) {
    return kUridAtomFloat;
  }
  if (std::strcmp(uri, LV2_ATOM__Long) == 0) {
    return kUridAtomLong;
  }
  if (std::strcmp(uri, LV2_ATOM__Sequence) == 0) {
    return kUridAtomSequence;
  }
  if (std::strcmp(uri, LV2_ATOM__String) == 0) {
    return kUridAtomString;
  }
  if (std::strcmp(uri, LV2_ATOM__Property) == 0) {
    return kUridAtomProperty;
  }
  if (std::strcmp(uri, LV2_MIDI__MidiEvent) == 0) {
    return kUridMidiEvent;
  }
  return 0;
};
