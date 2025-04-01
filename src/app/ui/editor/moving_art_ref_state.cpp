#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include "app/ui/editor/moving_art_ref_state.h"

#include "app/cmd/set_art_ref_bounds.h"
#include "app/console.h"
#include "app/commands/command.h"
#include "app/commands/commands.h"
#include "app/tx.h"
#include "app/ui/editor/editor.h"
#include "app/ui/editor/editor_hit.h"
#include "app/ui_context.h"
#include "ui/message.h"

#include <algorithm>
#include <cmath>

namespace app {

using namespace ui;

MovingArtRefState::MovingArtRefState(Editor* editor,
                                     ui::MouseMessage* msg,
                                     const EditorHit& hit,
                                     const doc::SelectedObjects& selectedArtRefs)
  : m_hit(hit)
  , m_items(std::max<std::size_t>(1, selectedArtRefs.size()))
{
  m_mouseStart = editor->screenToEditor(msg->position());

  if (selectedArtRefs.empty()) {
    m_items[0] = getItemForArtRef(m_hit.artRef());
  }
  else {
    int i = 0;
    for (ArtRef* artRef : selectedArtRefs.iterateAs<ArtRef>()) {
      ASSERT(artRef);
      m_items[i++] = getItemForArtRef(artRef);
    }
  }

  editor->captureMouse();
}

bool MovingArtRefState::onMouseUp(Editor* editor, MouseMessage* msg)
{
  Doc* doc = editor->document();

  {
    try {
      ContextWriter writer(UIContext::instance(), 1000);
      Tx tx(writer, "Art Ref Movement", ModifyDocument);

      for (const auto& item : m_items) {
        tx(new cmd::SetArtRefBoundsF(item.artRef, item.oldBounds));
        item.artRef->setBounds(item.newBounds);
      }

      tx.commit();
    }
    catch (const base::Exception& e) {
      Console::showException(e);
    }
  }
  editor->backToPreviousState();
  editor->releaseMouse();
  return true;
}

bool MovingArtRefState::onMouseMove(Editor* editor, MouseMessage* msg)
{
  gfx::Point newCursorPos = editor->screenToEditor(msg->position());
  gfx::Point delta = newCursorPos - m_mouseStart;
  gfx::Rect totalBounds = selectedArtRefsBounds();

  ASSERT(totalBounds.w > 0);
  ASSERT(totalBounds.h > 0);

  for (auto& item : m_items) {
    gfx::Rect rc(item.oldBounds);

    // Move art ref
    if (m_hit.border() == (CENTER | MIDDLE)) {
      rc.x += delta.x;
      rc.y += delta.y;
    }

    item.newBounds = rc;

    if (m_hit.type() == EditorHit::ArtRefBounds)
      item.artRef->setBounds(rc);
  }

  // Redraw the editor.
  editor->invalidate();

  // Use StandbyState implementation
  return StandbyState::onMouseMove(editor, msg);
}

bool MovingArtRefState::onSetCursor(Editor* editor, const gfx::Point& mouseScreenPos)
{
  editor->showMouseCursor(kArrowCursor);
  return true;
}

MovingArtRefState::Item MovingArtRefState::getItemForArtRef(doc::ArtRef* artRef)
{
  gfx::RectF bounds = artRef->bounds();

  Item item;
  item.artRef = artRef;
  item.oldBounds = gfx::Rect(bounds);
  item.newBounds = gfx::Rect(bounds);

  return item;
}

gfx::Rect MovingArtRefState::selectedArtRefsBounds() const
{
  gfx::Rect bounds;
  for (auto& item : m_items)
    bounds |= item.artRef->bounds();
  return bounds;
}

} // namespace app
