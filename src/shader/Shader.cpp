#include "Shader.h"

namespace GameEngine {
  std::string read_file(const char* filepath) {
    FILE* file = fopen(filepath, "rt");
    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    char* data = new char[length + 1];
    memset(data, 0, length + 1);
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);

    std::string result(data);
    delete[] data;
    return result;
  }

  Shader::Shader(const char* vertPath, const char* fragPath) : vertexShaderPath(vertPath), fragmentShaderPath(fragPath) {
    this->shaderId = load();
  }

  Shader::~Shader() {
    glDeleteProgram(shaderId);
  }

  GLuint Shader::load() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Get the vertex shader source code
    std::string vertSourceString = read_file(this->vertexShaderPath);
    const char* vertSource = vertSourceString.c_str();
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    // Compile the vertex shader and check for errors
    glCompileShader(vertexShader);
    GLint vertexShaderSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderSuccess);
    if (!vertexShaderSuccess) {
      GLint length;
      glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> error(length);
      glGetShaderInfoLog(vertexShader, length, &length, &error[0]);
      std::cout << "Failed to compile vertex shader!" << '\n' << &error[0] << '\n';
      glDeleteShader(vertexShader);
      return 0;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Get the fragment shader source code
    std::string fragSourceString = read_file(this->fragmentShaderPath);
    const char* fragSource = fragSourceString.c_str();
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    // Compile the fragment shader and check for errors
    glCompileShader(fragmentShader);
    GLint fragmentShaderSuccess;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSuccess);
    if (!fragmentShaderSuccess) {
      GLint length;
      glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> error(length);
      glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);
      std::cout << "Failed to compile fragment shader!" << '\n' << &error[0] << '\n';
      glDeleteShader(fragmentShader);
      return 0;
    }

    // Link the vertex and fragment shader into a shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint programSuccess;
    glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
    if (!programSuccess) {
      GLint length;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> error(length);
      glGetProgramInfoLog(program, length, &length, &error[0]);
      std::cout << "Failed to link shader program!" << '\n' << &error[0] << '\n';
      glDeleteProgram(program);
      return 0;
    }

    glValidateProgram(program);
    return program;
  }

  GLint Shader::getUniformLocation(const GLchar* name) {
    return glGetUniformLocation(shaderId, name);
  }

  void Shader::setUniform1f(const GLchar* name, float value) {
    glUniform1f(getUniformLocation(name), value);
  }

  void Shader::setUniform1i(const GLchar* name, int value) {
    glUniform1i(getUniformLocation(name), value);
  }

  void Shader::setUniform2f(const GLchar* name, const Vec2& vector) {
    glUniform2f(getUniformLocation(name), vector.x, vector.y);
  }

  void Shader::setUniform3f(const GLchar* name, const Vec3& vector) {
    glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
  }

  void Shader::setUniform4f(const GLchar* name, const Vec4& vector) {
    glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
  }

  void Shader::setUniformMat4(const GLchar* name, const Mat4& matrix) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
  }

  void Shader::enable() const {
    glUseProgram(shaderId);
  }

  void Shader::disable() const {
    glUseProgram(0);
  }
}
