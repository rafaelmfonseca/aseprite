#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "doc/art_ref.h"

#include "base/debug.h"
#include "doc/art_refs.h"

namespace doc {

ArtRef::ArtRef()
  : Object(ObjectType::ArtRef)
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

void ArtRef::setName(const std::string& name)
{
  m_name = name;
}

void ArtRef::setText(const std::string& text)
{
  m_text = text;
}

void ArtRef::setBounds(const gfx::Rect& bounds)
{
  m_bounds = bounds;
}

} // namespace doc
