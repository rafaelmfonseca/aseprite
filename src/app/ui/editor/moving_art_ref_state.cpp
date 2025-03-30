#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/ui/editor/moving_art_ref_state.h"

#include "app/ui/editor/editor.h"
#include "app/ui/editor/editor_hit.h"
#include "ui/message.h"

#include <algorithm>
#include <cmath>

namespace app {

using namespace ui;

MovingArtRefState::MovingArtRefState(Editor* editor,
                                     ui::MouseMessage* msg,
                                     const EditorHit& hit)
{
}

bool MovingArtRefState::onMouseUp(Editor* editor, MouseMessage* msg)
{
  editor->backToPreviousState();
  editor->releaseMouse();
  return true;
}

bool MovingArtRefState::onSetCursor(Editor* editor, const gfx::Point& mouseScreenPos)
{
  editor->showMouseCursor(kSizeNWCursor);
  return true;
}

} // namespace app
