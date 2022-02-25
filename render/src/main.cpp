// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>
#include <math.h>

#include <window/buffered_pane.h>
#include <context/camera.h>
#include <context/context.h>
#include <shaders/basic_shader.h>

#include <mathlib.h>
#include <filelib.h>

/**
 * height -> 0xff
 * line -> x
 *
 * x * height = line * 0xff
 * x = line * 0xff / height
 *
 */

class MyPane : public BaseBufferedPane
{
public:
  Context *context = nullptr;
  MyPane(wxFrame *parent) : BaseBufferedPane(parent) {}
  void Render(uint8_t *buffer, int w, int h) override
  {
    if (context == nullptr)
      return;
    std::cout << "Render" << std::endl;
    context->Render(buffer, w, h);
  }

  void KeyDown(int key) override
  {
    switch (key)
    {
    case (int)'R':
    {
      Reload();
      break;
    }
    default:
      break;
    }
  }

  void Reload()
  {
    delete context;
    context = new Context();

    File *file = new File("assets/vaso.byu");
    file->Load();

    Camera *c = Camera::FromFile("assets/camera.txt");
    c->SetSize(
        GetSize().GetWidth(),
        GetSize().GetHeight());
    context->Load(file->vertices, file->vertexCount, file->indices, file->triangleCount);
    context->SetCamera(c);
    context->UseShader(new BasicShader());
    std::cout << "Context loaded" << std::endl;
  }
};

class MyApp : public wxApp
{
  bool OnInit();

  wxFrame *frame;
  MyPane *drawPane;

public:
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame *)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(500, 500));

  drawPane = new MyPane((wxFrame *)frame);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();

  return true;
}

BEGIN_EVENT_TABLE(BaseBufferedPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BaseBufferedPane::mouseMoved)
 EVT_LEFT_DOWN(BaseBufferedPane::mouseDown)
 EVT_LEFT_UP(BaseBufferedPane::mouseReleased)
 EVT_RIGHT_DOWN(BaseBufferedPane::rightClick)
 EVT_LEAVE_WINDOW(BaseBufferedPane::mouseLeftWindow)
 EVT_KEY_DOWN(BaseBufferedPane::keyPressed)
 EVT_KEY_UP(BaseBufferedPane::keyReleased)
 EVT_MOUSEWHEEL(BaseBufferedPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(MyPane::PaintEvent)
EVT_SIZE(MyPane::SizeEvent)
EVT_KEY_DOWN(MyPane::KeyDownEvent)

END_EVENT_TABLE()