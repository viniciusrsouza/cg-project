#include <context/shader.h>

class BasicShader : public Shader
{
public:
  BasicShader() : Shader() {}
  ~BasicShader() {}

  vec4 Vertex(vec3 const &in)
  {
    vec4 v = view * vec4(in, 1.0f);
    vec4 p = (perspective * v) / v.z;
    return screen * p;
  }
  vec3 Fragment()
  {
    return vec3(1.0f, 1.0f, 1.0f);
  }
};