#include <iostream>
using namespace std;

#define FREEGLUT_STATIC
#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/freeglut.h>

// 3차원 좌표 표현하기위한 구조체
struct Vec3f
{
    float x, y, z;
    Vect3f(){}
    Vect3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

enum {TRIANGLE, N_VBOs};
GLuint VBO[N_VBOs]; // 꼭짓점 버퍼 객체

// 꼭짓점 셰이더 소스
static const char* pVS =
"#version 330                                       \n"
"layout(location = 0) in vec3 Position;             \n"
"                                                   \n"
"void main()                                        \n"
"{                                                  \n"
    "gl_Position = vec4(Position * 0.1, 1.0)"
"}";

// 프래그먼트 셰이더 소스
static const char* pFS =
"#version 330                                       \n"
"out vec4 FragColor;                                \n"
"                                                   \n"
"void main()                                        \n"
"{                                                  \n"
"FragColor = vec4(1.0, 0.0, 0.0, 1.0);              \n"
"}                                                  \n";

static void AddShader(GLuint shaderProg,
    const char* pShaderSrc, GLint ShaderType)
{ // 셰이더 생성
    GLuint shader = glCreateShader(ShaderType);
    if (!shader)
    {
        cerr << "오류 - Shader 생성 " << ShaderType << endl;
        exit(0);
    }

    // 셰이더 컴파일 
    const GLchar* src[1] = { pShaderSrc };
    const GLint len[1] = { strlen(pShaderSrc) };

    glShaderSource(shader, 1, src, len);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    // 컴파일 오류 발생시
    if (!success)
    {
        GLchar infoLog[256];
        glGetShaderInfoLog(shader, 256, NULL, infoLog);
        cerr << "오류 - Shader 컴파일" << ShaderType << ": " << infoLog << endl;
        exit(1);
    }
    // 셰이더 프로그램에 컴파일된 셰이더를 추가
    glAttachShader(shaderProg, shader);
}

// 셰이더 프로그램 객체 생성
static void SetUpShaders()
{
    GLuint shaderProg = glCreateProgram();
    if (!shaderProg)
    {
        cerr << "오류 - Shader 프로그램 생성 " << endl;
        exit(1);
    }

    // 꼭짓점 셰이더 및 프래그먼트 셰이더 적재
    AddShader(shaderProg, pVS, GL_VERTEX_SHADER);
    AddShader(shaderProg, pFS, GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errLog[256];
    
    // 셰이더 프로그램 링크
    glLinkProgram(shaderProg);
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProg, sizeof(errLog), NULL, errLog);
        cerr << "오류 - shader 프로그램 링크 : " << errLog << endl;
        exit(1);
    }

    glValidateProgram(shaderProg); // 프로그램 객체가 유효한 지 검사
    glGetProgramiv(shaderProg, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProg, sizeof(errLog), NULL, errLog);
        cerr << "INVALID SHADER PROGRAM" << errLog << endl;
        exit(1);
    }

    // 현재 셰이더 프로그램 객체로 지정
    glUseProgram(shaderProg);
}

static void RenderCB()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 백색으로 화면 지움

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glFinish();
}

static void InitVBOs()
{
    Vec3f Vertices[3];

}


int main()
{
    std::cout << "Hello World!\n";
    return 0;
}
