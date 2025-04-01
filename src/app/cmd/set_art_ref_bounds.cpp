#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/cmd/set_art_ref_bounds.h"

#include "doc/art_ref.h"

namespace app { namespace cmd {

using namespace doc;

SetArtRefBoundsF::SetArtRefBoundsF(ArtRef* artRef, const gfx::RectF& oldBounds)
  : WithArtRef(artRef)
  , m_oldBounds(oldBounds)
  , m_newBounds(artRef->bounds())
{
}

void SetArtRefBoundsF::onExecute()
{
  artRef()->setBounds(m_newBounds);
  artRef()->incrementVersion();
}

void SetArtRefBoundsF::onUndo()
{
  artRef()->setBounds(m_oldBounds);
  artRef()->incrementVersion();
}

}} // namespace app::cmd
