#include <shader.h>

class BasicShader : public Shader
{
public:
  BasicShader() : Shader() {}
  ~BasicShader() {}

  vec3 Vertex(vec3 const &in) const
  {
    vec3 v = camera->ToView(in);
    v = camera->ToPerspective(v);
    v = camera->ToScreen(v);
    return v;
  }
  vec3 Fragment() const
  {
    return vec3(1.0f, 1.0f, 1.0f);
  }
};