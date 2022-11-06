#include "shader.h"
#include <fstream>
#include <iostream>

Shader::Shader()

{
    
}

void Shader::init_shaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
    // Vertex Shader
      
    std::string v_source = read_shader_to_string(vertex_file_path);
    const char* v_c = v_source.c_str(); // Create a const char* so it lives in memory
    std::printf(v_c);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_c , NULL);
    glCompileShader(vertex_shader);
    checkError(vertex_shader);

    // Fragment Shader
    
    std::string f_source = read_shader_to_string(fragment_file_path);
    const char* f_c = f_source.c_str();

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_c,  NULL);
    glCompileShader(fragment_shader);
    checkError(fragment_shader);

    // Attach shaders to program
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glUseProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}

void Shader::use_shader()
{
    glUseProgram(program);
}

void Shader::setUniform1f(const char * uniformName, float value)
{  
    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program, uniformName), value);
}
void Shader::setUniformMat4f(const char* uniformName, glm::mat4 matrix)
{
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(this->program, uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string Shader::read_shader_to_string(const std::string& file_path)
{
    std::ifstream source(file_path);
    std::string final_string;
    for (std::string line = "";std::getline(source, line);)
    {
        final_string += line + "\n";
    }
    return final_string;
}

void Shader::checkError(unsigned int shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error, could not create shader!" <<  infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteProgram(this->program);
}