#ifndef DOC_ART_REF_H_INCLUDED
#define DOC_ART_REF_H_INCLUDED
#pragma once

#include "gfx/rect.h"

#include <string>

namespace doc {
class ArtRefs;
class Sprite;

// we don't want WithUserData here!
class ArtRef {
public:
  ArtRef();
  ~ArtRef();

  ArtRefs* owner() const { return m_owner; }

  const std::string& text() const { return m_text; }
  const gfx::Rect& bounds() const { return m_bounds; }

  void setOwner(ArtRefs* owner);
  void setText(const std::string& text) { m_text = text; }
  void setBounds(const gfx::Rect& bounds) { m_bounds = bounds; }

public:
  ArtRefs* m_owner;
  std::string m_text;
  gfx::Rect m_bounds;
};

} // namespace doc

#endif
