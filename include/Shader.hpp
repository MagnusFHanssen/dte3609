#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <windows.h>
#include <GL/glew.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "../../glm-master/glm/glm.hpp"


enum ShaderType {V_SHADER, F_SHADER};

class Shader 
{
	public:
		Shader();
		~Shader();
  
    // enable and disable program
    void enable();
    void disable();
    GLuint getProg();
    
    bool initShaders(char *fileName);

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;


	private:
  
    GLuint vs_, fs_, prog_;
    GLchar *vertexShaderSource_, *fragmentShaderSource_;

    int shaderSize(char *fileName, ShaderType shaderType);
    int readShader(char *fileName, ShaderType shaderType, 
                   char *shaderText, int size);
    int loadShaderSource(const GLchar *vertexShader, const GLchar *fragmentShader);

};

#endif //_SHADER_HPP_

