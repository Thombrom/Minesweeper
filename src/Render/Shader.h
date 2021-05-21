#pragma once
#include <glad/glad.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// constructor reads and builds the shader
	Shader();
	void set_vertex_shader(const char* _vertex_path);
	void set_geometry_shader(const char* _vertex_path);
	void set_fragment_shader(const char* _vertex_path);
	void compile();

	// use/activate the shader
	void use();

	// utility uniform functions
	void set_bool(const std::string &name, bool value) const;
	void set_int(const std::string &name, int value) const;
	void set_float(const std::string &name, float value) const;
	void set_vec3(const std::string &name, float _x, float _y, float _z);
	void set_mat4(const std::string &name, glm::mat4& _mat);

private:
	unsigned int ID;
	void check_compile_error(unsigned int shader, std::string type);
	void read_file(const char* _path, std::string& _out);

	enum ShaderType
	{
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2,
	};

	unsigned int shader_ids[3] = { 0 };
};