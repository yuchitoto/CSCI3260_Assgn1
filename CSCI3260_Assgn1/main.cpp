#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
using namespace std;
//using glm::vec3;
//using glm::mat4;

GLuint programID;
int norm = 0;
int growth = 0;
short cheshire_cat = 0;

float moved[3][3];
float camHeight = +0.0f;

std::ofstream logFile;

GLuint vao[7];

GLuint vbo[7];
GLuint vbo_ibo[7];

void sendDataToOpenGL()
{
	const GLfloat floor_vert[] =
	{
		-12.0f, +0.0f, -12.0f,
		+12.0f, +0.0f, -12.0f,
		+12.0f, +0.0f, +12.0f,
		-12.0f, +0.0f, +12.0f,
	};
	const GLfloat floor_color[] =
	{
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
	};
	const GLushort floor_ind[] =
	{
		1, 2, 4, 3
	};

	//vao 0 floor
	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vert)+sizeof(floor_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(floor_vert), floor_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(floor_vert), sizeof(floor_color), floor_color);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(floor_vert));

	//index
	glGenBuffers(1, &vbo_ibo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ibo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_ind), floor_ind, GL_STATIC_DRAW);
	
	//vao 1 mountain b
	//declare const
	const GLfloat bottle_vert[] =
	{
		//lower base
		-0.015f, +0.0f, -0.015f,
		+0.015f, +0.0f, -0.015f,
		+0.015f, +0.0f, +0.015f,
		-0.015f, +0.0f, +0.015f,
		//upper base
		-0.015f, +0.07f, -0.015f,
		+0.015f, +0.07f, -0.015f,
		+0.015f, +0.07f, +0.015f,
		-0.015f, +0.07f, +0.015f,
		//lower bottle neck
		-0.005f, +0.08f, -0.005f,
		+0.005f, +0.08f, -0.005f,
		+0.005f, +0.08f, +0.005f,
		-0.005f, +0.08f, +0.005f,
		//upper bottle neck
		-0.005f, +0.1f, -0.005f,
		+0.005f, +0.1f, -0.005f,
		+0.005f, +0.1f, +0.005f,
		-0.005f, +0.1f, +0.005f
	};
	const GLfloat bottle_color[] =
	{
		//base color #832A0D
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		//up color
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		//bottle neck base color
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		//bottle neck up color
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
		+0.513f, +0.164f, +0.050f,
	};
	const GLushort bottle_index[] =
	{
		0,1,3,2,7,8,8,2,5,1,4,0,7,3,7,7,11,4,8,5,9,6,10,7,11,11,8,12,9,13,10,14,11,15,12,14,13
	};

	glGenVertexArrays(1, &vao[1]);
	glBindVertexArray(vao[1]);
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bottle_vert) + sizeof(bottle_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bottle_vert), bottle_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bottle_vert), sizeof(bottle_color), bottle_color);

	//vao 1 vert
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//vao 1 color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(bottle_vert));

	//vao 1 index
	glGenBuffers(1, &vbo_ibo[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ibo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottle_index), bottle_index, GL_STATIC_DRAW);

	//vao 2
	const GLfloat cake_vert[] =
	{
		//bottom
		-0.11f, +0.0f, -0.11f,
		+0.11f, +0.0f, -0.11f,
		+0.11f, +0.0f, +0.11f,
		-0.11f, +0.0f, +0.11f,

		//top
		-0.11f, +0.15f, -0.11f,
		+0.11f, +0.15f, -0.11f,
		+0.11f, +0.15f, +0.11f,
		-0.11f, +0.15f, +0.11f
	};
	const GLfloat cake_color[] =
	{
		+0.823f, +0.411f, +0.117f,
		+0.823f, +0.411f, +0.117f,
		+0.823f, +0.411f, +0.117f,
		+0.823f, +0.411f, +0.117f,

		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
	};
	const GLushort cake_ind[] =
	{
		0,1,3,2,2,0,0,4,1,5,2,6,3,7,0,4,4,5,7,6
	};

	glGenVertexArrays(1, &vao[2]);
	glBindVertexArray(vao[2]);
	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cake_vert) + sizeof(cake_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cake_vert), cake_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cake_vert), sizeof(cake_color), cake_color);

	//cake vert
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//cake color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(cake_vert));

	//cake ind
	glGenBuffers(1, &vbo_ibo[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ibo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cake_ind), cake_ind, GL_STATIC_DRAW);

	const GLfloat table_vert[] =
	{
		//up surf 0.71
		-0.3f, +0.71f, -0.3f,
		+0.3f, +0.71f, -0.3f,
		+0.3f, +0.71f, +0.3f,
		-0.3f, +0.71f, +0.3f,
		//low surf 0.7
		-0.3f, +0.70f, -0.3f,
		+0.3f, +0.70f, -0.3f,
		+0.3f, +0.70f, +0.3f,
		-0.3f, +0.70f, +0.3f,
		//leg
		-0.15f, +0.70f, -0.15f,
		+0.15f, +0.70f, -0.15f,
		+0.15f, +0.70f, +0.15f,
		-0.15f, +0.70f, +0.15f,

		-0.1f, +0.35f, -0.1f,
		+0.1f, +0.35f, -0.1f,
		+0.1f, +0.35f, +0.1f,
		-0.1f, +0.35f, +0.1f,

		-0.15f, +0.0f, -0.15f,
		+0.15f, +0.0f, -0.15f,
		+0.15f, +0.0f, +0.15f,
		-0.15f, +0.0f, +0.15f
	};
	const GLfloat table_color[] =
	{
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
	};
	const GLushort table_ind[] =
	{
		0,1,3,2,2,0,0,4,1,5,2,6,3,7,0,4,4,8,5,9,6,10,7,11,4,8,8,12,9,13,10,14,11,13,8,12,12,16,13,17,10,18,15,19,12,16
	};

	glGenVertexArrays(1, &vao[3]);
	glBindVertexArray(vao[3]);
	glGenBuffers(1, &vbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(table_vert) + sizeof(table_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(table_vert), table_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(table_vert), sizeof(table_color), table_color);

	//table vert
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//table color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(table_vert));

	//table ind
	glGenBuffers(1, &vbo_ibo[3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(table_ind), table_ind, GL_STATIC_DRAW);

	//vao 4, 5 chair
	const GLfloat chair_vert[] =
	{
		//base
		-0.2f, +0.0f, -0.2f,
		+0.2f, +0.0f, -0.2f, 
		+0.2f, +0.0f, +0.2f, 
		-0.2f, +0.0f, +0.2f,

		-0.05f, +0.15f, -0.05f,
		+0.05f, +0.15f, -0.05f,
		+0.05f, +0.15f, +0.05f, 
		-0.05f, +0.15f, +0.05f,

		//seat 19
		-0.2f, +0.15f, -0.2f,
		+0.2f, +0.15f, -0.2f,
		+0.2f, +0.15f, +0.2f,
		-0.2f, +0.15f, +0.2f,

		-0.2f, +0.19f, -0.2f,
		+0.2f, +0.19f, -0.2f,
		+0.2f, +0.19f, +0.2f,
		-0.2f, +0.19f, +0.2f,

		//slant
		-0.2f, +0.19f, +0.22f,
		+0.2f, +0.19f, +0.22f,

		//back 0.59
		-0.2f, +0.59f, +0.2f,
		+0.2f, +0.59f, +0.2f, 
		+0.2f, +0.59f, +0.22f,
		-0.2f, +0.59f, +0.22f,

		//top 0.69
		+0.0f, +0.69f, +0.2f,
		+0.0f, +0.69f, +0.22f
	};
	const GLfloat chair_color[] =
	{
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
	};
	const GLushort chair_ind[] =
	{
		0,1,3,2,2,0,0,4,1,5,2,6,3,7,0,4,4,8,5,9,6,10,7,11,4,8,8,12,9,13,10,14,11,15,8,12,12,13,15,14,14,11,11,15,16,14,17,10,10,15,15,18,14,19,17,20,16,21,15,18,18,21,22,23,19,20,20,21,23,23,22,22,18,19
	};

	glGenVertexArrays(1, &vao[4]);
	glBindVertexArray(vao[4]);
	glGenBuffers(1, &vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(chair_vert) + sizeof(chair_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(chair_vert), chair_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(chair_vert), sizeof(chair_color), chair_color);

	//vao 4 v
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//vao 4 c
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(chair_vert));

	//vao 4 i
	glGenBuffers(1, &vbo_ibo[4]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ibo[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(chair_ind), chair_ind, GL_STATIC_DRAW);

	//vao 5
	glGenVertexArrays(1, &vao[5]);
	glBindVertexArray(vao[5]);
	glGenBuffers(1, &vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(chair_vert) + sizeof(chair_color), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(chair_vert), chair_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(chair_vert), sizeof(chair_color), chair_color);

	//vao 5 v
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//vao 5 c
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(chair_vert));

	//vao 5 i
	glGenBuffers(1, &vbo_ibo[5]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ibo[5]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(chair_ind), chair_ind, GL_STATIC_DRAW);

	//cheshire cat
	const GLfloat cc_vert[] =
	{
		//mouth
		-0.12f, +0.0f, +0.0f,
		+0.12f, +0.0f, +0.0f,
		+0.0f, -0.06f, +0.0f,
		+0.0f, -0.10f, +0.0f,
		//lft eye
		-0.12f, +0.07f, +0.0f,
		-0.085f, +0.10f, +0.0f,
		-0.05f, +0.07f, +0.0f,
		-0.085f, +0.04f, +0.0f,

		-0.085f, +0.07f, +0.0f,

		-0.09f, +0.07f, +0.0f,
		-0.08f, +0.07f, +0.0f,
		//rht eye
		+0.12f, +0.07f, +0.0f,
		+0.085f, +0.10f, +0.0f,
		+0.05f, +0.07f, +0.0f,
		+0.085f, +0.04f, +0.0f,

		+0.085f, +0.07f, +0.0f,

		+0.09f, +0.07f, +0.0f,
		+0.08f, +0.07f, +0.0f,
	};
	const GLfloat cc_color[] =
	{
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,

		+1.0f, +1.0f, +1.0f,
		+0.0f, +0.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
		+0.0f, +0.0f, +0.0f,

		+1.0f, +1.0f, +1.0f,

		+0.0f, +0.0f, +0.0f,
		+0.0f, +0.0f, +0.0f,

		+1.0f, +1.0f, +1.0f,
		+0.0f, +0.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
		+0.0f, +0.0f, +0.0f,

		+1.0f, +1.0f, +1.0f,

		+0.0f, +0.0f, +0.0f,
		+0.0f, +0.0f, +0.0f,
	};
	const GLushort cc_ind[] =
	{
		0, 2, 3,
		2, 3, 1,
		4, 5, 9,
		4, 9, 7,
		5, 9, 8,
		9, 8, 7,
		7, 8, 10,
		10, 8, 5,
		5, 10, 6,
		10, 6, 7,
		13, 17, 12,
		13, 14, 17,
		14, 17, 15,
		17, 15, 12,
		12, 15, 16,
		15, 16, 14,
		14, 16, 11,
		11, 16, 12
	};

	glGenVertexArrays(1, &vao[6]);
	glBindVertexArray(vao[6]);
	glGenBuffers(1, &vbo[6]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cc_color) + sizeof(cc_vert), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cc_vert), cc_vert);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cc_vert), sizeof(cc_color), cc_color);

	//cat v
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//cat c
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (char*)sizeof(cc_vert));

	//cat i
	glGenBuffers(1, &vbo_ibo[6]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[6]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cc_ind), cc_ind, GL_STATIC_DRAW);
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;
	glUseProgram(programID);

}

void initializedGL(void) //run only once
{
	sendDataToOpenGL();
	installShaders();
}

void wiederkunft(void)
{
	moved[0][0] = 0.0f;	moved[0][1] = 0.0f;	moved[0][2] = 0.0f;
	moved[1][0] = 0.0f;	moved[1][1] = 0.0f;	moved[1][2] = 0.0f;
	moved[2][0] = 0.0f;	moved[2][1] = 0.0f;	moved[2][2] = 0.0f;
}

void tobemoved(int growth_dir)
{
	///now takes 100s to move to designated position
	switch (growth_dir)
	{
	case 1:
		camHeight += (camHeight < +1.0f) ? +0.00025f : +0.0f;
		moved[0][0] += (moved[0][0] < +0.89f) ? +0.0002225f : +0.0f;
		moved[0][2] += (moved[0][2] < +0.448f) ? +0.000112f : +0.0f;
		moved[1][0] += (moved[1][0] < +0.61f) ? +0.0001525f : +0.0f;
		moved[1][2] += (moved[1][2] < +0.34f) ? +0.000085f : +0.0f;
		moved[2][0] += (moved[2][0] < +0.92f) ? +0.00023f : +0.0f;
		moved[2][2] += (moved[2][2] < +0.4f) ? +0.0001f : +0.0f;
		break;
	case -1:
		camHeight -= (camHeight > -1.0f) ? +0.00025f : +0.0f;
		moved[0][0] -= (moved[0][0] > +0.0f) ? +0.0002225f : +0.0f;
		moved[0][2] -= (moved[0][2] > +0.0f) ? +0.000112f : +0.0f;
		moved[1][0] -= (moved[1][0] > +0.0f) ? +0.0001525f : +0.0f;
		moved[1][2] -= (moved[1][2] > +0.0f) ? +0.000085f : +0.0f;
		moved[2][0] -= (moved[2][0] > +0.0f) ? +0.00023f : +0.0f;
		moved[2][2] -= (moved[2][2] > +0.0f) ? +0.0001f : +0.0f;
		break;
	//case 0:
	}
}

void alice_growth(void)
{
	growth;	//each pos gorwth unit move all things 1 meter away from alice
	//glutTimerFunc
	switch (growth)
	{
	case 0:
		wiederkunft();
		break;
	default:
		glutTimerFunc(25, tobemoved, growth);
	}
}

void paintGL(void)  //always run
{
	glClearColor(0.8f, 0.7f, 0.7f, 1.0f); //specify the background color

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	alice_growth();

	glBindVertexArray(vao[0]); //floor
	glm::mat4 modelTransformMatrix = glm::mat4(1.0f);
	modelTransformMatrix = glm::translate(glm::mat4(), glm::vec3(+0.0f, +0.0f, +0.0f));
	GLint modelTransformMatrixUniformLocation = glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::lookAt(glm::vec3(-4.0f, +1.75f + camHeight, -4.0f), glm::vec3(+4.0f, +0.71f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f));
	GLint viewMatrixUniformLocation = glGetUniformLocation(programID, "viewMatrix");
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.1f, 10.0f);
	GLint projectionMarixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);


	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0); //render primitives from array data

	glBindVertexArray(vao[1]); //draw bottle

	modelTransformMatrix = (growth<0)?glm::scale(glm::mat4(), glm::vec3(+0.0001f, +0.0001f, +0.0001f)):glm::mat4(1.0f);
	modelTransformMatrix = glm::translate(modelTransformMatrix, glm::vec3(+4.0f, +0.71f, +0.0f));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLE_STRIP, 37, GL_UNSIGNED_SHORT, 0);	//end bottle

	glBindVertexArray(vao[2]); //draw cake

	modelTransformMatrix = (growth>0)?glm::scale(glm::mat4(), glm::vec3(+0.0001f, +0.0001f, +0.0001f)):glm::mat4(1.0f);
	modelTransformMatrix = glm::translate(modelTransformMatrix, glm::vec3(+3.5f, +0.0f, +0.0f));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_SHORT, 0);	//end cake

	glBindVertexArray(vao[3]); //table

	modelTransformMatrix = glm::mat4(1.0f);
	modelTransformMatrix = glm::translate(glm::mat4(), glm::vec3(+4.0f + moved[0][0], +0.0f + moved[0][1], +0.0f + moved[0][2]));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);


	glDrawElements(GL_TRIANGLE_STRIP, 46, GL_UNSIGNED_SHORT, 0);	//end table

	glBindVertexArray(vao[4]); //chair1

	modelTransformMatrix = (growth < 1) ? glm::mat4(1.0f) : glm::rotate(glm::mat4(1.0f), 0.513f, glm::vec3(+0.0f, +1.0f, +0.0f));
	modelTransformMatrix = glm::translate(modelTransformMatrix, glm::vec3(+0.4f + moved[1][0], +0.0f + moved[1][1], +0.5f + moved[1][2]));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLE_STRIP, 74, GL_UNSIGNED_SHORT, 0);	//end chair1

	glBindVertexArray(vao[5]);	//chair2

	modelTransformMatrix = glm::mat4(1.0f);
	modelTransformMatrix = glm::rotate(glm::mat4(), glm::radians((growth < 1) ? +135.0f : +45.0f), glm::vec3(+0.0f, +1.0f, +0.0f));
	modelTransformMatrix = glm::translate(modelTransformMatrix, glm::vec3(+4.0f + moved[2][0], +0.0f + moved[2][1], -0.5f + moved[2][2]));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLE_STRIP, 74, GL_UNSIGNED_SHORT, 0);	//end chair2

	glBindVertexArray(vao[6]);	//cheshire cat

	modelTransformMatrix = glm::mat4(1.0f);
	modelTransformMatrix = glm::rotate(glm::mat4(), 0.620f, glm::vec3(+0.0f, +1.0f, +0.0f));
	modelTransformMatrix = glm::translate(modelTransformMatrix, glm::vec3(+3.0f, (cheshire_cat > 0) ? +0.2f : -3.0f, +1.0f));
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	viewMatrix = viewMatrix;
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	projectionMatrix = projectionMatrix;
	glUniformMatrix4fv(projectionMarixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_SHORT, 0);	//end cheshire cat
	
	glFlush(); //force execution of GL commands
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'e')
	{
		growth = +1;
		logFile << "eat me called" << std::endl;
	}
	if (key == 'd')
	{
		growth = -1;
		logFile << "drink me called" << std::endl;
	}
	if (key == 'c')
	{
		cheshire_cat = (cheshire_cat == 0) ? 1 : 0;
		logFile << "cheshire cat called " << cheshire_cat << std::endl;
	}
	if (key == 'r')
	{
		growth = 0;
		logFile << "ewige wiederkunft!!!" << std::endl;
	}
}


int main(int argc, char* argv[])
{
	logFile.open("log.txt", std::ofstream::out | std::ofstream::trunc);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	//glutInitWindowPosition()
	glutCreateWindow(argv[0]); // window title
	glewInit();

	initializedGL();

	glutDisplayFunc(paintGL);
	glutKeyboardFunc(keyboard);

	glutMainLoop(); //call display callback over and over
}