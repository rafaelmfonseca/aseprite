#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "doc/art_ref.h"

#include "base/debug.h"
#include "doc/art_refs.h"

namespace doc {

ArtRef::ArtRef()
{
}

ArtRef::~ArtRef()
{
  ASSERT(!m_owner);
}

void ArtRef::setOwner(ArtRefs* owner)
{
  m_owner = owner;
}

} // namespace doc
