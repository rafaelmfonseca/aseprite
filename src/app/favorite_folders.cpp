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

namespace {

  const char* kSectionName[] = { "FavoriteFolders", "FavoriteFoldersLabels" };

} // namespace

namespace app {

//////////////////////////////////////////////////////////////////////
// FavoriteEntry
FavoriteEntry::FavoriteEntry(const std::string& path,
                             const std::string& label)
  : m_path(path)
  , m_label(label)
{
}

base::paths FavoriteEntry::listFiles()
{
  base::paths files;
  for (const auto& file : base::list_files(m_path, base::ItemType::Files)) {
    files.push_back(base::join_path(m_path, file));
  }

  return files;
}

//////////////////////////////////////////////////////////////////////
// FavoriteFolders
FavoriteFolders::FavoriteFolders()
{
  load();
}

void FavoriteFolders::load()
{
  const char* section1 = kSectionName[0];
  const char* section2 = kSectionName[1];

  for (const auto& key : enum_config_keys(section1)) {
    const char* fn = get_config_string(section1, key.c_str(), nullptr);
    const char* fn2 = get_config_string(section2, key.c_str(), nullptr);

    if (fn && fn2 && base::is_directory(fn)) {
      std::string normalFn = base::normalize_path(fn);

      auto menuitem = new FavoriteEntry(normalFn, fn2);
      m_favorites.push_back(menuitem);
    }
  }
}

}