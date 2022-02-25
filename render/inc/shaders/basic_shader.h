#include <context/shader.h>

class BasicShader : public Shader
{
public:
  BasicShader() : Shader() {}
  ~BasicShader() {}

  vec3 Vertex(vec3 const &in)
  {
    vec3 v = camera->ToView(in);
    v = camera->ToPerspective(v);
    v = camera->ToScreen(v);
    return v;
  }
  vec3 Fragment()
  {
    return vec3(1.0f, 1.0f, 1.0f);
  }
};