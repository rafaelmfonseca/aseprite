#ifndef DOC_ART_REF_IO_H_INCLUDED
#define DOC_ART_REF_IO_H_INCLUDED
#pragma once

#include "doc/serial_format.h"

#include <iosfwd>

namespace doc {

class ArtRef;

void write_art_ref(std::ostream& os, const ArtRef* artRef);
ArtRef* read_art_ref(std::istream& is, bool setId = true);

} // namespace doc

#endif
