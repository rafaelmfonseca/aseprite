#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "doc/art_refs.h"

#include "base/debug.h"
#include "doc/art_ref.h"

#include <algorithm>

namespace doc {

ArtRefs::ArtRefs(Sprite* sprite) : m_sprite(sprite)
{
}

ArtRefs::~ArtRefs()
{
  for (ArtRef* artRef : m_artRefs) {
    artRef->setOwner(nullptr);
    delete artRef;
  }
}

void ArtRefs::add(ArtRef* artRef)
{
  m_artRefs.push_back(artRef);
  artRef->setOwner(this);
}

} // namespace doc
