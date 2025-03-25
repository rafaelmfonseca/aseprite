#ifndef APP_FAVORITE_FOLDERS_H_INCLUDED
#define APP_FAVORITE_FOLDERS_H_INCLUDED
#pragma once

#include "base/paths.h"

#include <string>
#include <vector>

namespace app {

class FavoriteFolders {

public:
  const base::paths& favoriteFolders() const { return m_paths; }

  FavoriteFolders();

private:
  void load();

  base::paths m_paths;
};

} // namespace app

#endif
