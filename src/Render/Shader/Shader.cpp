#include "Shader.h"

Shader::Shader()
{
	// Currently empty
}

void Shader::read_file(const char* _path, std::string& _out)
{
	std::ifstream file;
	 
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(_path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		_out = stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::set_vertex_shader(const char* _vertex_path)
{
	std::string code;
	read_file(_vertex_path, code);

	const char* shader_code = code.c_str();
	shader_ids[ShaderType::VERTEX] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader_ids[ShaderType::VERTEX], 1, &shader_code, NULL);
	glCompileShader(shader_ids[ShaderType::VERTEX]);
	check_compile_error(shader_ids[ShaderType::VERTEX], "VERTEX");
}

void Shader::set_fragment_shader(const char* _fragment_path)
{
	std::string code;
	read_file(_fragment_path, code);

	const char* shader_code = code.c_str();
	shader_ids[ShaderType::FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_ids[ShaderType::FRAGMENT], 1, &shader_code, NULL);
	glCompileShader(shader_ids[ShaderType::FRAGMENT]);
	check_compile_error(shader_ids[ShaderType::FRAGMENT], "FRAGMENT");
}

void Shader::set_geometry_shader(const char* _geometry_path)
{
	std::string code;
	read_file(_geometry_path, code);

	const char* shader_code = code.c_str();
	shader_ids[ShaderType::GEOMETRY] = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(shader_ids[ShaderType::GEOMETRY], 1, &shader_code, NULL);
	glCompileShader(shader_ids[ShaderType::GEOMETRY]);
	check_compile_error(shader_ids[ShaderType::GEOMETRY], "GEOMETRY");
}

void Shader::compile()
{
	ID = glCreateProgram();
	if (shader_ids[ShaderType::VERTEX])   glAttachShader(ID, shader_ids[ShaderType::VERTEX]);
	if (shader_ids[ShaderType::FRAGMENT]) glAttachShader(ID, shader_ids[ShaderType::FRAGMENT]);
	if (shader_ids[ShaderType::GEOMETRY]) glAttachShader(ID, shader_ids[ShaderType::GEOMETRY]);
	glLinkProgram(ID);
	check_compile_error(ID, "PROGRAM");

	// Delete shaders, we don't need them anymore
	if (shader_ids[ShaderType::VERTEX])   glDeleteShader(shader_ids[ShaderType::VERTEX]);
	if (shader_ids[ShaderType::FRAGMENT]) glDeleteShader(shader_ids[ShaderType::FRAGMENT]);
	if (shader_ids[ShaderType::GEOMETRY]) glDeleteShader(shader_ids[ShaderType::GEOMETRY]);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::destroy()
{
    glDeleteProgram(ID);
}

void Shader::set_bool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_vec3(const std::string &name, float _x, float _y, float _z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), _x, _y, _z);
}

void Shader::set_mat4(const std::string &name, const glm::mat4& _mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &_mat[0][0]);
}

void Shader::check_compile_error(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
