#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/cmd/with_art_ref.h"

#include "doc/art_ref.h"

namespace app { namespace cmd {

WithArtRef::WithArtRef(ArtRef* artRef) : m_artRefId(artRef->id())
{
}

ArtRef* WithArtRef::artRef()
{
  return get<ArtRef>(m_artRefId);
}

}} // namespace app::cmd