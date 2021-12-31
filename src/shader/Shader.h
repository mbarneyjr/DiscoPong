#pragma once

#include <iostream>
#include <vector>
#include <glad/gl.h>

#include "../math/Vec2.h"
#include "../math/Vec3.h"
#include "../math/Vec4.h"
#include "../math/Mat4.h"

namespace GameEngine {
  std::string read_file(const char* filepath);

  class Shader {
  private:
    GLuint shaderId;
    const char* vertexShaderPath;
    const char* fragmentShaderPath;
  public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    void setUniform1f(const GLchar* name, float value);
    void setUniform1i(const GLchar* name, int value);
    void setUniform2f(const GLchar* name, const Vec2& vector);
    void setUniform3f(const GLchar* name, const Vec3& vector);
    void setUniform4f(const GLchar* name, const Vec4& vector);
    void setUniformMat4(const GLchar* name, const Mat4& matrix);

    void enable() const;
    void disable() const;
  private:
    GLuint load();
    GLint getUniformLocation(const GLchar* name);
  };
}
