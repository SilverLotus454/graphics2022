#include "Shader.h"

Shader::Shader()
{

}

/*#################################################################
##  ����: Shader
##  ���������� Shader��Ĺ��캯�������ڴ�������Vertex Shader��Fragment
Shader��Shader Program����IDΪprogramID��
##  ����������
##  vertexPath: Vertex Shader��Դ��·��
##  fragmentPath: Fragment Shader��Դ��·��
###################################################################*/
Shader::Shader(std::string const vertexPath, std::string const fragmentPath)
{
	// -----------------���ļ�·���л�ȡ����/Ƭ����ɫ��---------------------
	std::string vertexCode;			// Vertex ShaderԴ���ַ���
	std::string fragmentCode;		// FragmentShaderԴ���ַ���
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ��֤ifstream��������׳��쳣��
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// ���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// ��ȡ�ļ��Ļ������ݵ���������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();
		// ת����������string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("��ȡShader�ļ�ʧ�ܣ�\n");
		printf("vertexPath:%s\n", vertexPath);
		printf("fragmentPath:%s\n", fragmentPath);
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// -------------------------------������ɫ��-------------------------------
	unsigned int vertexShaderID, fragmentShaderID;	// ��ɫ��ID������������ɫ��
	int success;									// ��ɫ�������Ƿ�ɹ�
	char infoLog[512];
	// ������ɫ��
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);		// ����������ɫ��
	glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);  // ��ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShaderID);						// ������ɫ��
	// ������������ӡ������Ϣ
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		printf("\nVertex Shader������󣡴�����Ϣ��\n%s\n", infoLog);
		printf("Vertex ShaderԴ�룺\n%s\n", vShaderCode);
	};

	// Ƭ����ɫ��
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);	  // ����Fragment��ɫ��
	glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);  // ��ɫ��Դ�븽�ӵ���ɫ�������ϣ��ڶ�������ָ������Դ���ַ���������
	glCompileShader(fragmentShaderID);						  // ������ɫ��
	// ������������ӡ������Ϣ
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success); // ����Ƿ����ɹ�
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		printf("\nFragment Shader������󣡴�����Ϣ��\n%s\n", infoLog);
		printf("Fragment ShaderԴ�룺\n%s\n", fShaderCode);
	};

	// ------------------------������������ɫ������---------------------------
	programID = glCreateProgram();					// ������ɫ������
	glAttachShader(programID, vertexShaderID);		// ����ɫ�����󸽼ӵ�����ɫ������
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);						// ����
	// �������ʧ�ܣ���ӡ���Ӵ���
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		printf("������ɫ������ʧ�ܣ�\n������Ϣ��%s\n", infoLog);
	}

	// ɾ����ɫ������
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

/*###################################################
##  ����: use
##  ���������� ʹ����ɫ������
##  ���������� ��
#####################################################*/
void Shader::use()
{
	glUseProgram(programID);
}

/*###################################################
##  ����: setBool
##  ���������� ������ɫ����bool���͵�uniform��ֵ
##  ���������� 
##  name: uniform������
##  value: Ҫ���õ�uniform��ֵ
#####################################################*/
void Shader::setBool(const std::string &name, bool value) const
{
	// �����ɫ������Ϊname��uniform��λ��ֵ
	int loc = glGetUniformLocation(programID, name.c_str());
	// ���¸�uniform��ֵ��ע�⣺����uniform֮ǰ���������glUseProgram
	glUniform1i(loc, (int)value);
}

/*###################################################
##  ����: setInt
##  ���������� ������ɫ����int���͵�uniform��ֵ
##  ����������
##  name: uniform������
##  value: Ҫ���õ�uniform��ֵ
#####################################################*/
void Shader::setInt(const std::string &name, int value) const
{
	// �����ɫ������Ϊname��uniform��λ��ֵ
	int loc = glGetUniformLocation(programID, name.c_str());
	// ���¸�uniform��ֵ
	glUniform1i(loc, value);
}

/*###################################################
##  ����: setFloat
##  ���������� ������ɫ����float���͵�uniform��ֵ
##  ����������
##  name: uniform������
##  value: Ҫ���õ�uniform��ֵ
#####################################################*/
void Shader::setFloat(const std::string &name, float value) const
{
	// �����ɫ������Ϊname��uniform��λ��ֵ
	int loc = glGetUniformLocation(programID, name.c_str());
	// ���¸�uniform��ֵ
	glUniform1f(loc, value);
}

/*###################################################
##  ����: setVec3
##  ���������� ������ɫ����vec3���͵�uniform��ֵ
##  ����������
##  name: uniform������
##  value1: Ҫ���õ�vec3��xֵ
##  value2: Ҫ���õ�vec3��yֵ
##  value3: Ҫ���õ�vec3��zֵ
#####################################################*/
void Shader::setVec3(const std::string &name, float value1, float value2, float value3) const
{
	int loc = glGetUniformLocation(programID, name.c_str());
	glUniform3f(loc, value1, value2, value3);
}


void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}