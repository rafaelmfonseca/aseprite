#ifndef APP_UI_EDITOR_MOVING_ART_REF_STATE_H_INCLUDED
#define APP_UI_EDITOR_MOVING_ART_REF_STATE_H_INCLUDED
#pragma once

#include "app/ui/editor/editor_hit.h"
#include "app/ui/editor/standby_state.h"
#include "doc/art_ref.h"

namespace app {
class Editor;

class MovingArtRefState : public StandbyState {
public:
  MovingArtRefState(Editor* editor,
                    ui::MouseMessage* msg,
                    const EditorHit& hit,
                    // TODO: Check this later
                    doc::ArtRef* artRef);

  bool onMouseUp(Editor* editor, ui::MouseMessage* msg) override;
  bool onMouseMove(Editor* editor, ui::MouseMessage* msg) override;

  bool onSetCursor(Editor* editor, const gfx::Point& mouseScreenPos) override;

private:
  // TODO: Check this later
  gfx::Point m_mouseStart;
  doc::ArtRef* m_selected;
};

} // namespace app

#endif // APP_UI_EDITOR_MOVING_ART_REF_STATE_H_INCLUDED