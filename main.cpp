#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "objloader.hpp"
#include "include/shader_m.h"
#include "include/camera.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int screenWidth = 1900;
const unsigned int screenHeight = 500;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float escala=3.0f;

FT_Face face;
FT_Library ft;

GLuint vertexbufferSol;
GLuint colorbufferSol;
GLuint SolVAO;

GLuint vertexbufferMercurio;
GLuint colorbufferMercurio;
GLuint MercurioVAO;

GLuint vertexbufferVenus;
GLuint colorbufferVenus;
GLuint VenusVAO;

GLuint vertexbufferTerra;
GLuint colorbufferTerra;
GLuint TerraVAO;

GLuint vertexbufferLua;
GLuint colorbufferLua;
GLuint LuaVAO;

GLuint vertexbufferMarte;
GLuint colorbufferMarte;
GLuint MarteVAO;

GLuint vertexbufferJupiter;
GLuint colorbufferJupiter;
GLuint JupiterVAO;

GLuint vertexbufferSaturno;
GLuint colorbufferSaturno;
GLuint SaturnoVAO;

GLuint vertexbufferUrano;
GLuint colorbufferUrano;
GLuint UranoVAO;

GLuint vertexbufferNeptuno;
GLuint colorbufferNeptuno;
GLuint NeptunoVAO;
// color buffer object (CBO)
GLuint colorbuffer;
// lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::mat4 modelSol = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 modelMercurio = glm::mat4(1.0f);

// GLSL program from the shaders
GLuint programID;
GLuint VertexArrayID;
// Matrix id of the MVP
GLuint MatrixID;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
std::vector< glm::vec3 > vertices;
glm::vec3 objectPosition = glm::vec3(5.8f/escala, 0.0f, 0.0f);

std::vector< glm::vec3 > verticesSol;
std::vector< glm::vec2 > uvsSol;
std::vector< glm::vec3 > normalsSol;
glm::vec3 solPosition = glm::vec3(5.8f/escala, 0.0f, 0.0f);
bool resSol = loadOBJ("Planetas/Sol.obj", verticesSol, uvsSol, normalsSol);

std::vector< glm::vec3 > verticesMercurio;
std::vector< glm::vec2 > uvsMercurio;
std::vector< glm::vec3 > normalsMercurio;
glm::vec3 mercurioPosition = glm::vec3(5.8f/escala, 0.0f, 0.0f);
bool resMercurio = loadOBJ("Planetas/Mercurio.obj", verticesMercurio, uvsMercurio, normalsMercurio);


std::vector< glm::vec3 > verticesVenus;
std::vector< glm::vec2 > uvsVenus;
std::vector< glm::vec3 > normalsVenus;
glm::vec3 venusPosition = glm::vec3(10.8f/escala, 0.0f, 0.0f);
bool resVenus = loadOBJ("Planetas/Venus.obj", verticesVenus, uvsVenus, normalsVenus);


std::vector< glm::vec3 > verticesTerra;
std::vector< glm::vec2 > uvsTerra;
std::vector< glm::vec3 > normalsTerra;
glm::vec3 terraPosition = glm::vec3(15.0f/escala, 0.0f, 0.0f);
bool resTerra = loadOBJ("Planetas/Terra.obj", verticesTerra, uvsTerra, normalsTerra);


std::vector< glm::vec3 > verticesLua;
std::vector< glm::vec2 > uvsLua;
std::vector< glm::vec3 > normalsLua;
glm::vec3 luaPosition = glm::vec3(15.5f/escala, 0.0f, 0.0f);
bool resLua = loadOBJ("Planetas/Lua.obj", verticesLua, uvsLua, normalsLua);


std::vector< glm::vec3 > verticesMarte;
std::vector< glm::vec2 > uvsMarte;
std::vector< glm::vec3 > normalsMarte;
glm::vec3 martePosition = glm::vec3(23.0f/escala, 0.0f, 0.0f);
bool resMarte = loadOBJ("Planetas/Marte.obj", verticesMarte, uvsMarte, normalsMarte);


std::vector< glm::vec3 > verticesJupiter;
std::vector< glm::vec2 > uvsJupiter;
std::vector< glm::vec3 > normalsJupiter;
glm::vec3 jupiterPosition = glm::vec3(78.0f/escala, 0.0f, 0.0f);
bool resJupiter = loadOBJ("Planetas/Jupiter.obj", verticesJupiter, uvsJupiter, normalsJupiter);


std::vector< glm::vec3 > verticesSaturno;
std::vector< glm::vec2 > uvsSaturno;
std::vector< glm::vec3 > normalsSaturno;
glm::vec3 saturnoPosition = glm::vec3(143.0f/escala, 0.0f, 0.0f);
bool resSaturno = loadOBJ("Planetas/Saturno.obj", verticesSaturno, uvsSaturno, normalsSaturno);


std::vector< glm::vec3 > verticesUrano;
std::vector< glm::vec2 > uvsUrano;
std::vector< glm::vec3 > normalsUrano;
glm::vec3 uranoPosition = glm::vec3(287.0f/escala, 0.0f, 0.0f);
bool resUrano = loadOBJ("Planetas/Urano.obj", verticesUrano, uvsUrano, normalsUrano);


std::vector< glm::vec3 > verticesNeptuno;
std::vector< glm::vec2 > uvsNeptuno;
std::vector< glm::vec3 > normalsNeptuno;
glm::vec3 neptunoPosition = glm::vec3(450.0f/escala, 0.0f, 0.0f);
bool resNeptuno = loadOBJ("Planetas/Neptuno.obj", verticesNeptuno, uvsNeptuno, normalsNeptuno);


//glm::vec3 rotatePosition = glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat delta = 0.00f;
GLfloat angulo = 0.0f;

GLfloat anguloMercurio = 0.0f;
GLfloat anguloVenus = 0.0f;
GLfloat anguloTerra = 0.0f;
GLfloat anguloLua = 0.0f;
GLfloat anguloMarte = 0.0f;
GLfloat anguloJupiter = 0.0f;
GLfloat anguloSaturno = 0.0f;
GLfloat anguloUrano = 0.0f;
GLfloat anguloNeptuno = 0.0f;

float speedScale=1.0f;


float MercurioRotationSpeed=0.041477f * speedScale;
float VenusRotationSpeed=0.01622 * speedScale;
float TerraRotationSpeed = 0.01f * speedScale;
float LuaRotationSpeed = 0.1f * speedScale;
float MarteRotationSpeed = 0.0053129548762736535662299854439592f * speedScale;
float JupiterRotationSpeed = 0.0008425669436749769159741458910434f * speedScale;
float SaturnoRotationSpeed = 0.000339219330855018587360594795539f * speedScale;
float UranoRotationSpeed = 0.0001189661353932401160327238355986f * speedScale;
float NeptunoRotationSpeed = 0.0000606413025419504901146369828875f * speedScale;


glm::vec3 calcularPosicaoLua(const glm::vec3& posicaoTerra, float anguloOrbitalLua, float raioOrbitalLua) {
    // Calcule as coordenadas x e z da posição orbital da Lua usando funções trigonométricas
    float posX = posicaoTerra.x + raioOrbitalLua * glm::cos(anguloOrbitalLua);
    float posZ = posicaoTerra.z + raioOrbitalLua * glm::sin(anguloOrbitalLua);

    // Mantenha a coordenada y constante ou ajuste conforme necessário, dependendo do plano orbital
    float posY = posicaoTerra.y; // ou ajuste conforme necessário

    // Retorne a posição tridimensional da Lua
    return glm::vec3(posX, posY, posZ);
}

bool checkPlanetClick(const glm::vec3& planetPosition, float planetRadius, const glm::vec3& clickRayOrigin, const glm::vec3& clickRayDirection) {
    glm::vec3 oc = clickRayOrigin - planetPosition;
    float a = glm::dot(clickRayDirection, clickRayDirection);
    float b = 2.0f * glm::dot(oc, clickRayDirection);
    float c = glm::dot(oc, oc) - planetRadius * planetRadius;
    float discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

void renderText(const char *text, GLfloat x, GLfloat y, GLfloat fontSize, FT_Face face) {
    // Criar shaders
    const char* vertexShaderSource = "shaders/vertex_shader.glsl"; // Substitua com o código do vertex shader
    const char* fragmentShaderSource = "shaders/fragment_shader.glsl"; // Substitua com o código do fragment shader
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // Criar programa de shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    FT_GlyphSlot g = face->glyph;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint textColorLoc = glGetUniformLocation(shaderProgram, "textColor");
    glUseProgram(shaderProgram);
    glUniform3f(textColorLoc, 1.0f, 1.0f, 1.0f); // Set text color

    // Configurar o VBO (Vertex Buffer Object) e o VAO (Vertex Array Object)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Atributos de vértice (posição)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    GLfloat xpos = x;
    GLfloat ypos = y;

    for (const char *p = text; *p; p++) {
        if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) {
            continue;
        }

        GLfloat x2 = xpos + g->bitmap_left * fontSize;
        GLfloat y2 = -ypos - g->bitmap_top * fontSize;
        GLfloat w = g->bitmap.width * fontSize;
        GLfloat h = g->bitmap.rows * fontSize;

        GLfloat vertices[6][2] = {
                {x2,     -y2},
                {x2 + w, -y2},
                {x2,     -y2 - h},
                {x2,     -y2 - h},
                {x2 + w, -y2},
                {x2 + w, -y2 - h}
        };

        // Atualizar o conteúdo do buffer do VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Renderizar o caractere usando os vértices
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Atualizar a posição para o próximo caractere
        xpos += (g->advance.x >> 6) * fontSize;
        ypos += (g->advance.y >> 6) * fontSize;
    }

    // Limpar configurações do OpenGL
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glDisable(GL_BLEND);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(0);
    // Libere a face após usar
    FT_Done_Face(face);
    // Libere a biblioteca FreeType após concluir todas as operações
    //FT_Done_FreeType(ft);
}






int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Inicialização do FreeType
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Erro ao inicializar FreeType" << std::endl;
        return -1;
    }

    // Carregamento da face da fonte
    if (FT_New_Face(ft, "SpaceGrotesk-Medium.ttf", 0, &face)) {
        std::cerr << "Erro ao carregar a face da fonte" << std::endl;
        return -1;
    }
    // Configurar tamanho da fonte
    FT_Set_Pixel_Sizes(face, 0, 48);


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    
    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("shaders/2.1.basic_lighting.vs", "shaders/2.1.basic_lighting.fs");
    Shader lampShader("shaders/2.1.lamp.vs", "shaders/2.1.lamp.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    // VAO
    unsigned int Sol, sol;
    glGenVertexArrays(1, &sol);
    glGenBuffers(1, &Sol);

    // Move vertex data to video memory; specifically to Sol called vertexbuffer
    bool res = loadOBJ("Planetas/Sol.obj", vertices, uvs, normals);
    glBindBuffer(GL_ARRAY_BUFFER, Sol);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glBindVertexArray(sol);

    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (Sol stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, Sol);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //MERCURIO
    glGenVertexArrays(1, &MercurioVAO);
    glGenBuffers(1, &vertexbufferMercurio);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferMercurio);
    glBufferData(GL_ARRAY_BUFFER, verticesMercurio.size() * sizeof(glm::vec3), &verticesMercurio[0], GL_STATIC_DRAW);
    glBindVertexArray(MercurioVAO);

    glGenBuffers(1, &colorbufferMercurio);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferMercurio);
    glBufferData(GL_ARRAY_BUFFER, verticesMercurio.size() * sizeof(glm::vec3), &verticesMercurio[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //VENUS
    glGenVertexArrays(1, &VenusVAO);
    glGenBuffers(1, &vertexbufferVenus);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferVenus);
    glBufferData(GL_ARRAY_BUFFER, verticesVenus.size() * sizeof(glm::vec3), &verticesVenus[0], GL_STATIC_DRAW);
    glBindVertexArray(VenusVAO);

    glGenBuffers(1, &colorbufferVenus);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferVenus);
    glBufferData(GL_ARRAY_BUFFER, verticesVenus.size() * sizeof(glm::vec3), &verticesVenus[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //SOL
    glGenVertexArrays(1, &SolVAO);
    glGenBuffers(1, &vertexbufferSol);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferSol);
    glBufferData(GL_ARRAY_BUFFER, verticesSol.size() * sizeof(glm::vec3), &verticesSol[0], GL_STATIC_DRAW);
    glBindVertexArray(SolVAO);

    glGenBuffers(1, &colorbufferSol);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferSol);
    glBufferData(GL_ARRAY_BUFFER, verticesSol.size() * sizeof(glm::vec3), &verticesSol[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //TERRA
    glGenVertexArrays(1, &TerraVAO);
    glGenBuffers(1, &vertexbufferTerra);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferTerra);
    glBufferData(GL_ARRAY_BUFFER, verticesTerra.size() * sizeof(glm::vec3), &verticesTerra[0], GL_STATIC_DRAW);
    glBindVertexArray(TerraVAO);

    glGenBuffers(1, &colorbufferTerra);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferTerra);
    glBufferData(GL_ARRAY_BUFFER, verticesTerra.size() * sizeof(glm::vec3), &verticesTerra[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //LUA
    glGenVertexArrays(1, &LuaVAO);
    glGenBuffers(1, &vertexbufferLua);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferLua);
    glBufferData(GL_ARRAY_BUFFER, verticesLua.size() * sizeof(glm::vec3), &verticesLua[0], GL_STATIC_DRAW);
    glBindVertexArray(LuaVAO);

    glGenBuffers(1, &colorbufferLua);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferLua);
    glBufferData(GL_ARRAY_BUFFER, verticesLua.size() * sizeof(glm::vec3), &verticesLua[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //MARTE
    glGenVertexArrays(1, &MarteVAO);
    glGenBuffers(1, &vertexbufferMarte);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferMarte);
    glBufferData(GL_ARRAY_BUFFER, verticesMarte.size() * sizeof(glm::vec3), &verticesMarte[0], GL_STATIC_DRAW);
    glBindVertexArray(MarteVAO);

    glGenBuffers(1, &colorbufferMarte);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferMarte);
    glBufferData(GL_ARRAY_BUFFER, verticesMarte.size() * sizeof(glm::vec3), &verticesMarte[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //JUPITER
    glGenVertexArrays(1, &JupiterVAO);
    glGenBuffers(1, &vertexbufferJupiter);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferJupiter);
    glBufferData(GL_ARRAY_BUFFER, verticesJupiter.size() * sizeof(glm::vec3), &verticesJupiter[0], GL_STATIC_DRAW);
    glBindVertexArray(JupiterVAO);

    glGenBuffers(1, &colorbufferJupiter);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferJupiter);
    glBufferData(GL_ARRAY_BUFFER, verticesJupiter.size() * sizeof(glm::vec3), &verticesJupiter[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //SATURNO
    glGenVertexArrays(1, &SaturnoVAO);
    glGenBuffers(1, &vertexbufferSaturno);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferSaturno);
    glBufferData(GL_ARRAY_BUFFER, verticesSaturno.size() * sizeof(glm::vec3), &verticesSaturno[0], GL_STATIC_DRAW);
    glBindVertexArray(SaturnoVAO);

    glGenBuffers(1, &colorbufferSaturno);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferSaturno);
    glBufferData(GL_ARRAY_BUFFER, verticesSaturno.size() * sizeof(glm::vec3), &verticesSaturno[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //URANO
    glGenVertexArrays(1, &UranoVAO);
    glGenBuffers(1, &vertexbufferUrano);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferUrano);
    glBufferData(GL_ARRAY_BUFFER, verticesUrano.size() * sizeof(glm::vec3), &verticesUrano[0], GL_STATIC_DRAW);
    glBindVertexArray(UranoVAO);

    glGenBuffers(1, &colorbufferUrano);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferUrano);
    glBufferData(GL_ARRAY_BUFFER, verticesUrano.size() * sizeof(glm::vec3), &verticesUrano[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //NEPTUNO
    glGenVertexArrays(1, &NeptunoVAO);
    glGenBuffers(1, &vertexbufferNeptuno);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferNeptuno);
    glBufferData(GL_ARRAY_BUFFER, verticesNeptuno.size() * sizeof(glm::vec3), &verticesNeptuno[0], GL_STATIC_DRAW);
    glBindVertexArray(NeptunoVAO);

    glGenBuffers(1, &colorbufferNeptuno);
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferNeptuno);
    glBufferData(GL_ARRAY_BUFFER, verticesNeptuno.size() * sizeof(glm::vec3), &verticesNeptuno[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Renderização de texto
        renderText("Seu Texto Aqui", 1500.0f, 250.0f, 200.0f,face);  // Use o tamanho desejado


        MercurioRotationSpeed=0.041477f * speedScale;
        VenusRotationSpeed=0.01622 * speedScale;
        TerraRotationSpeed = 0.01f * speedScale;
        LuaRotationSpeed = 0.1f * speedScale;
        MarteRotationSpeed = 0.0053129548762736535662299854439592f * speedScale;
        JupiterRotationSpeed = 0.0008425669436749769159741458910434f * speedScale;
        SaturnoRotationSpeed = 0.000339219330855018587360594795539f * speedScale;
        UranoRotationSpeed = 0.0001189661353932401160327238355986f * speedScale;
        NeptunoRotationSpeed = 0.0000606413025419504901146369828875f * speedScale;
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);
        
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.996f, 0.0f, 0.1f);
        lightingShader.setVec3("lightColor", 0.5f, 0.5f, 0.337f);
        lightingShader.setVec3("lightPos", lightPos);
        
        // view/projection transformations
        float fov = 45.0f; // FOV em graus
        float nearPlane = 0.1f; // plano próximo
        float farPlane = 1000.0f; // plano distante

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation

        lightingShader.setMat4("model", modelSol);


        // also draw the lamp object
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        modelSol = glm::mat4(1.0f);
        modelSol = glm::translate(modelSol, lightPos);
        modelSol = glm::scale(modelSol, glm::vec3(0.333f)); // a smaller cube
        lampShader.setMat4("model", modelSol);

        glBindVertexArray(SolVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);

        // Render Mercurio
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 1.0f, 0.192f);  // Set color for Mercurio
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Mercurio
        modelMercurio = glm::translate(glm::mat4(1.0f), mercurioPosition);
        modelMercurio = glm::rotate(modelMercurio, anguloMercurio, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotação em torno do eixo y
        modelMercurio = glm::scale(modelMercurio, glm::vec3(escala));
        lightingShader.setMat4("model", modelMercurio);

        // Bind Mercurio VAO and render
        glBindVertexArray(MercurioVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Mercurio VAO

        // Render Venus
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.776f, 0.286f);  // Set color for Venus
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Venus
        model = glm::translate(glm::mat4(1.0f), venusPosition);
        model = glm::rotate(model, angulo, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Venus VAO and render
        glBindVertexArray(VenusVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Venus VAO

        // Render Terra
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.0f, 1.0f, 0.0f);  // Set color for Terra
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Terra
        model = glm::translate(glm::mat4(1.0f), terraPosition);
        model = glm::rotate(model, anguloTerra, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Terra VAO and render
        glBindVertexArray(TerraVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Terra VAO

        // Render Terra
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);  // Set color for Terra
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Terra
        model = glm::translate(glm::mat4(1.0f), luaPosition);
        model = glm::rotate(model, anguloLua, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Terra VAO and render
        glBindVertexArray(LuaVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Terra VAO

        // Render Marte
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.611f, 0.18f, 0.208f);  // Set color for Marte
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Marte
        model = glm::translate(glm::mat4(1.0f), martePosition);
        model = glm::rotate(model, anguloMarte, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Marte VAO and render
        glBindVertexArray(MarteVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Marte VAO

        // Render Jupiter
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.847f, 0.792f, 0.615f);  // Set color for Marte
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Marte
        model = glm::translate(glm::mat4(1.0f), jupiterPosition);
        model = glm::rotate(model, anguloJupiter, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Marte VAO and render
        glBindVertexArray(JupiterVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Jupiter VAO

        // Render Saturno
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.9f, 0.5f);  // Set color for Marte
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Jupiter
        model = glm::translate(glm::mat4(1.0f), saturnoPosition);
        model = glm::rotate(model, anguloSaturno, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Jupiter VAO and render
        glBindVertexArray(SaturnoVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3000*3);
        glBindVertexArray(0);  // Unbind Jupiter VAO

        // Render Urano
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.0f, 1.0f);  // Set color for Marte
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Urano
        model = glm::translate(glm::mat4(1.0f), uranoPosition);
        model = glm::rotate(model, anguloUrano, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Urano VAO and render
        glBindVertexArray(UranoVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Marte VAO

        // Render Urano
        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.50f, 0.5f, 1.0f);  // Set color for Marte
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);

        // Set model matrix for Urano
        model = glm::translate(glm::mat4(1.0f), neptunoPosition);
        model = glm::rotate(model, anguloNeptuno, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(escala));
        lightingShader.setMat4("model", model);

        // Bind Urano VAO and render
        glBindVertexArray(NeptunoVAO);
        glDrawArrays(GL_TRIANGLES, 0, 960*3);
        glBindVertexArray(0);  // Unbind Marte VAO



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &sol);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &Sol);
    glDeleteVertexArrays(1, &MercurioVAO);
    glDeleteBuffers(1, &vertexbufferMercurio);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Converta as coordenadas do mouse para um raio no espaço 3D
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, screenWidth, screenHeight);
    glm::vec3 clickRayOrigin, clickRayDirection;
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

    clickRayOrigin = glm::unProject(glm::vec3(xpos, ypos, 0.0f), camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 1000.0f), viewport);
    clickRayDirection = glm::normalize(glm::unProject(glm::vec3(xpos, ypos, 1.0f), camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 1000.0f), viewport) - clickRayOrigin);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        speedScale=speedScale+0.01f;
    }
    if ((glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) && speedScale>0.01f ){
        speedScale=speedScale-0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.MovementSpeed+=0.5f;
    if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) && (camera.MovementSpeed>0.5f))
        camera.MovementSpeed-=0.1f;




    // Rotação do objeto
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        anguloMercurio += MercurioRotationSpeed;
        anguloVenus += VenusRotationSpeed;
        anguloTerra += TerraRotationSpeed;
        anguloMarte += MarteRotationSpeed;
        anguloJupiter += JupiterRotationSpeed;
        anguloSaturno += SaturnoRotationSpeed;
        anguloUrano += UranoRotationSpeed;
        anguloNeptuno += NeptunoRotationSpeed;
        anguloLua += LuaRotationSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        anguloMercurio -= MercurioRotationSpeed;
        anguloVenus -= VenusRotationSpeed;
        anguloTerra -= TerraRotationSpeed;
        anguloMarte -= MarteRotationSpeed;
        anguloJupiter -= JupiterRotationSpeed;
        anguloSaturno -= SaturnoRotationSpeed;
        anguloUrano -= UranoRotationSpeed;
        anguloNeptuno -= NeptunoRotationSpeed;
        anguloLua -= LuaRotationSpeed;
    }


    mercurioPosition = glm::vec3(glm::cos(anguloMercurio) * 5.8/escala, 0.0f, glm::sin(anguloMercurio) * 5.8/escala);
    venusPosition = glm::vec3(glm::cos(anguloVenus) * 10.8/escala, 0.0f, glm::sin(anguloVenus) * 10.8/escala);
    terraPosition = glm::vec3(glm::cos(anguloTerra) * 15.0/escala, 0.0f, glm::sin(anguloTerra) * 15.0/escala);
    martePosition = glm::vec3(glm::cos(anguloMarte) * 23.0/escala, 0.0f, glm::sin(anguloMarte) * 23.0/escala);
    jupiterPosition = glm::vec3(glm::cos(anguloJupiter) * 78.0/escala, 0.0f, glm::sin(anguloJupiter) * 78.0/escala);
    saturnoPosition = glm::vec3(glm::cos(anguloSaturno) * 143.0/escala, 0.0f, glm::sin(anguloSaturno) * 143.0/escala);
    uranoPosition = glm::vec3(glm::cos(anguloUrano) * 287.0/escala, 0.0f, glm::sin(anguloUrano) * 287.0/escala);
    neptunoPosition = glm::vec3(glm::cos(anguloNeptuno) * 450.0/escala, 0.0f, glm::sin(anguloNeptuno) * 450.0/escala);
    luaPosition= calcularPosicaoLua(terraPosition,anguloLua,0.5f);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(mercurioPosition, 0.1f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Mercurio é clicado
            std::cout << "\n";
            std::cout << "Planeta: Mercúrio\nDiametro: 4,879.4 KM\nMassa: 3.285 × 10^23 KG\nDuraçao do dia: 88 d " << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(venusPosition, 0.1f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Venus é clicado
            std::cout << "\n";
            std::cout << "Planeta: Vênus\nDiametro: 12,104 KM\nMassa: 4.867 × 10^24 KG\nDuraçao do dia: 243d " << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(terraPosition, 0.1f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Terra é clicado
            std::cout << "\n";
            std::cout << "Planeta: Terra\nDiametro: 12,742 KM\nMassa: 5.972 × 10^24 KG\nDuraçao do dia: 1d :) " << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(martePosition, 0.1f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Marte é clicado
            std::cout << "\n";
            std::cout << "Planeta: Marte\nDiametro: 6,779 KM\nMassa: 6.39 × 10^23 KG\nDuraçao do dia: 1d 0h 37m" << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(jupiterPosition, 1.0f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Jupiter é clicado
            std::cout << "\n";
            std::cout << "Planeta: Jupiter\nDiametro: 139,820 KM\nMassa: 1.898 × 10^27 KG\nDuraçao do dia: 0d 9h 56m" << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(saturnoPosition, 0.5f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Saturno é clicado
            std::cout << "\n";
            std::cout << "Planeta: Saturno\nDiametro: 116,460 KM\nMassa: 5.683 × 10^26 KG\nDuraçao do dia: 0d 10h 34m" << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(uranoPosition, 0.5f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Uranos é clicado
            std::cout << "\n";
            std::cout << "Planeta: Urano\nDiametro: 50,724 KM\nMassa: 8.681 × 10^25 KG\nDuraçao do dia: 0d 17h 14m" << std::endl;
        }
        // Verifique se algum planeta foi clicado
        if (checkPlanetClick(neptunoPosition, 0.5f, clickRayOrigin, clickRayDirection)) {
            // Ação quando Neptuno é clicado
            std::cout << "\n";
            std::cout << "Planeta: Neptuno\nDiametro: 49,244 KM\nMassa: 1.024 × 10^26 KG\nDuraçao do dia: 0d 16h 6m" << std::endl;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.02;

    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

