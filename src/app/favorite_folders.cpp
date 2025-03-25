#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/favorite_folders.h"

#include "app/ini_file.h"
#include "base/fs.h"
#include "fmt/format.h"
#include "ui/alert.h"

#include <cstdio>
#include <cstring>
#include <set>

namespace app {

FavoriteFolders::FavoriteFolders()
{
  load();
}

void FavoriteFolders::load()
{
  const char* section = "FavoriteFolders";

  for (const auto& key : enum_config_keys(section)) {
    const char* fn = get_config_string(section, key.c_str(), nullptr);

    if (fn && base::is_directory(fn)) {
      std::string normalFn = base::normalize_path(fn);
      m_paths.push_back(normalFn);

      /*
      ui::Alert::show(fmt::format(
        "FavoriteFolder Added"
        "<<key = \"{0}\""
        "<<value = \"{1}\"",
        key, normalFn));
      */
    }
  }
}

}