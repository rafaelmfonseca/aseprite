#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "doc/art_ref_io.h"

#include "base/serialization.h"
#include "doc/art_ref.h"
#include "doc/string_io.h"
#include "fixmath/fixmath.h"

#include <iostream>
#include <memory>

namespace doc {

using namespace base::serialization;
using namespace base::serialization::little_endian;

void write_art_ref(std::ostream& os, const ArtRef* artRef)
{
  write32(os, artRef->id());
  write_string(os, artRef->name());
  write_string(os, artRef->text());
  write32(os, artRef->bounds().x);
  write32(os, artRef->bounds().y);
  write32(os, artRef->bounds().w);
  write32(os, artRef->bounds().h);
}

ArtRef* read_art_ref(std::istream& is, const bool setId)
{
  ObjectId id = read32(is);
  std::string name = read_string(is);
  std::string text = read_string(is);

  int x = read32(is);
  int y = read32(is);
  int w = read32(is);
  int h = read32(is);

  std::unique_ptr<ArtRef> artRef(new ArtRef);
  artRef->setName(name);
  artRef->setText(text);
  artRef->setBounds(gfx::Rect(x, y, w, h));

  if (setId)
    artRef->setId(id);

  return artRef.release();
}

} // namespace doc
