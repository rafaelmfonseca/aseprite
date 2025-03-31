#ifndef APP_UI_EDITOR_MOVING_ART_REF_STATE_H_INCLUDED
#define APP_UI_EDITOR_MOVING_ART_REF_STATE_H_INCLUDED
#pragma once

#include "app/ui/editor/editor_hit.h"
#include "app/ui/editor/standby_state.h"
#include "doc/selected_objects.h"
#include "doc/art_ref.h"

namespace app {
class Editor;

class MovingArtRefState : public StandbyState {
public:
  MovingArtRefState(Editor* editor,
                    ui::MouseMessage* msg,
                    const EditorHit& hit,
                    const doc::SelectedObjects& selectedArtRefs);

  bool onMouseUp(Editor* editor, ui::MouseMessage* msg) override;
  bool onMouseMove(Editor* editor, ui::MouseMessage* msg) override;
  bool onSetCursor(Editor* editor, const gfx::Point& mouseScreenPos) override;

private:
  struct Item {
    doc::ArtRef* artRef;
    gfx::Rect oldBounds;
  };

  Item getItemForArtRef(doc::ArtRef* artRef);
  gfx::Rect selectedArtRefsBounds() const;

  EditorHit m_hit;
  gfx::Point m_mouseStart;
  std::vector<Item> m_items;
};

} // namespace app

#endif