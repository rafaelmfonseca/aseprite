#ifndef DOC_ART_REF_H_INCLUDED
#define DOC_ART_REF_H_INCLUDED
#pragma once

#include "doc/object.h"
#include "gfx/rect.h"

#include <string>

namespace doc {
class ArtRefs;

class ArtRef : public Object {
public:
  ArtRef();
  ~ArtRef();

  ArtRefs* owner() const { return m_owner; }
  const std::string& name() const { return m_name; }
  const std::string& text() const { return m_text; }
  const gfx::Rect& bounds() const { return m_bounds; }

  void setOwner(ArtRefs* owner);
  void setName(const std::string& name);
  void setText(const std::string& text);
  void setBounds(const gfx::Rect& bounds);

private:
  ArtRefs* m_owner;
  std::string m_name;
  std::string m_text;
  gfx::Rect m_bounds;
};

} // namespace doc

#endif
