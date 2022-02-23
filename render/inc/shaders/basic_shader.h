#include <context/shader.h>

class BasicShader : public Shader
{
public:
  BasicShader()
  {
  }
  ~BasicShader()
  {
  }

  void Vertex(vec3 in) {}
  vec3 Fragment()
  {
    return vec3(1.0f, 1.0f, 1.0f);
  }
};