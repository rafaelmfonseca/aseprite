#ifndef DOC_ART_REFS_H_INCLUDED
#define DOC_ART_REFS_H_INCLUDED
#pragma once

#include "base/disable_copying.h"

#include <string>
#include <vector>

namespace doc {

class ArtRef;
class Sprite;

class ArtRefs {
  typedef std::vector<ArtRef*> List;

public:
  typedef List::iterator iterator;
  typedef List::const_iterator const_iterator;

  ArtRefs(Sprite* sprite);
  ~ArtRefs();

  void add(ArtRef* artRef);

  iterator begin() { return m_artRefs.begin(); }
  iterator end() { return m_artRefs.end(); }
  const_iterator begin() const { return m_artRefs.begin(); }
  const_iterator end() const { return m_artRefs.end(); }

  std::size_t size() const { return m_artRefs.size(); }
  bool empty() const { return m_artRefs.empty(); }

private:
  Sprite* m_sprite;
  List m_artRefs;

  DISABLE_COPYING(ArtRefs);
};

} // namespace doc

#endif