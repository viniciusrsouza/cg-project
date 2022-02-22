#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

#include <utils/timer.h>

class BaseBufferedPane : public wxPanel
{

public:
  BaseBufferedPane(wxFrame *parent);

  void PaintEvent(wxPaintEvent &evt);
  void SizeEvent(wxSizeEvent &evt);
  void KeyDownEvent(wxKeyEvent &evt);
  void PaintNow();

  virtual void Render(uint8_t *buffer, int size);
  virtual void KeyDown(int key);

  // some useful events
  /*
   void mouseMoved(wxMouseEvent& event);
   void mouseDown(wxMouseEvent& event);
   void mouseWheelMoved(wxMouseEvent& event);
   void mouseReleased(wxMouseEvent& event);
   void rightClick(wxMouseEvent& event);
   void mouseLeftWindow(wxMouseEvent& event);
   void keyPressed(wxKeyEvent& event);
   void keyReleased(wxKeyEvent& event);
   */

  DECLARE_EVENT_TABLE()
private:
  uint8_t *frontBuffer;
  uint8_t *backBuffer;
  uint8_t *blankBuffer;
  Timer *timer;
  bool resizing = false;

  void DispatchPaint();
  void SwapBuffers();
  void PerformPaint(wxDC &dc);
  void InitBuffers();
  int GetBufferSize();
};