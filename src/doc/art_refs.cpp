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

void ArtRefs::remove(ArtRef* artRef)
{
  auto it = std::find(m_artRefs.begin(), m_artRefs.end(), artRef);
  ASSERT(it != m_artRefs.end());
  if (it != m_artRefs.end())
    m_artRefs.erase(it);

  artRef->setOwner(nullptr);
}

ArtRef* ArtRefs::getByName(const std::string& name) const
{
  for (ArtRef* artRef : *this) {
    if (artRef->name() == name)
      return artRef;
  }
  return nullptr;
}

ArtRef* ArtRefs::getById(ObjectId id) const
{
  for (ArtRef* artRef : *this) {
    if (artRef->id() == id)
      return artRef;
  }
  return nullptr;
}

} // namespace doc
