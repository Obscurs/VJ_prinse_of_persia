#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture menu_tex;
	Sprite *sprite;
};

#endif // _MENU_INCLUDE