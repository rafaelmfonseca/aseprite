#ifndef APP_CMD_WITH_ART_REF_H_INCLUDED
#define APP_CMD_WITH_ART_REF_H_INCLUDED
#pragma once

#include "doc/object_id.h"

namespace doc {
class ArtRef;
}

namespace app { namespace cmd {
using namespace doc;

class WithArtRef {
public:
  WithArtRef(ArtRef* artRef);
  ArtRef* artRef();

private:
  ObjectId m_artRefId;
};

}} // namespace app::cmd

#endif
