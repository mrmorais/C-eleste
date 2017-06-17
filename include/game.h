#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <list>

#include "snake.h"
#include "maze_reader.h"
#include "celeste.h"
#include "container.h"
#include "cell.h"

#define WINDOW_WIDTH 840
#define WINDOW_HEIGHT 480
#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3


class Game
{
	public:
		Game();			// Constructor
		void run();
	private:
		Celeste m_celeste;
		void processEvents();
		void render();
		void render_status();
		void mountScene(std::vector< std::vector<Cell> >, const Snake &);
	private:
		sf::RenderWindow mWindow;
		sf::Texture snake_textures[4];
		sf::Sprite mBoard;
		std::list< sf::Sprite > mSnake;
		std::list<sf::Sprite> mElements;
		std::map<int, sf::Texture> mTextures;
		StatusBoard m_status_board;
};

#endif
