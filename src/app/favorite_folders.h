#ifndef APP_FAVORITE_FOLDERS_H_INCLUDED
#define APP_FAVORITE_FOLDERS_H_INCLUDED
#pragma once

#include <string>
#include <vector>

namespace app {

class FavoriteEntry {
public:
  FavoriteEntry(const std::string& path, const std::string& label);

  const std::string& path() const { return m_path; }
  const std::string& label() const { return m_label; }
private:
  std::string m_path;
  std::string m_label;
};

typedef std::vector<FavoriteEntry*> FavoriteEntries;

class FavoriteFolders {
public:
  const FavoriteEntries& favoriteFolders() const { return m_favorites; }

  FavoriteFolders();
  
private:
  void load();

  FavoriteEntries m_favorites;
};

} // namespace app

#endif
