#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

/*
 Tutorial from: http://antongerdelan.net/opengl/hellotriangle.html
 */
int main() {
	glfwInit();
	
	int major = 3;
	int minor = 3;
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, major);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, minor);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwOpenWindow(640, 480, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);
        glewExperimental = GL_TRUE;     // Apparantly glew isn't detecting glGenVertexArrays support :(
	glewInit();
	
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported: %s\n", version);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	unsigned int vertexBufferObject = 0;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &points[0], GL_STATIC_DRAW);
	
        unsigned int vertexAttributeObject = 0;
        glGenVertexArrays(1, &vertexAttributeObject);
	glBindVertexArray(vertexAttributeObject);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	
        std::string vertexShaderSource =
			"in vec3 vp;"
			"void main() {"
			"    gl_Position = vec4(vp, 1.0);"
			"}";
	
	std::string fragmentShaderSource =
			"out vec4 fragColour;"
			"void main() {"
			"    fragColour = vec4(0.5, 0.0, 0.5, 1.0);"
			"}";
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* shaderSourceString = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &shaderSourceString, NULL);
        glCompileShader(vertexShader);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSourceString = fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSourceString, NULL);
        glCompileShader(fragmentShader);
        
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, fragmentShader);
        glAttachShader(shaderProgram, vertexShader);
        glLinkProgram(shaderProgram);
        
        bool running = true;
        while (running) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(vertexAttributeObject);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers();
            running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
        }
        
	glfwTerminate();
	return 0;
}
