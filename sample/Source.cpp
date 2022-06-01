#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include <time.h>
#include "Game.h"
using namespace sf;
using namespace std;
int random(int const nbMin,int const nbMax)
{
	//static std::random_device rd;
	static std::default_random_engine engine;
	std::uniform_int_distribution<> distribution(nbMin, nbMax);
	
	return distribution(engine);
}
float randomreal(float const nbMin, float const nbMax)
{
	
	static std::default_random_engine engine;
	std::uniform_real_distribution<> distribution(nbMin, nbMax);

	return distribution(engine);
}
void drawrectangle(int rectnumber, RectangleShape rect, RenderWindow &window)
{
	

		for (int i = 0;i < rectnumber;i++)
		{
			rect.setSize(Vector2f(random(50, 300), random(50, 300)));
			rect.setFillColor(Color(random(0, 255), random(0, 255), random(0, 255)));
			rect.setPosition(Vector2f(random(0, 800), random(0, 600)));
			rect.setOutlineThickness(1);
			rect.setOutlineColor(Color::Black);
			window.draw(rect);
				
		}
	
	
}

int width  = 800 ,height=600;
int subdivisions = 600;
int min_diff = 15;
int origin = 0;
int outline_thickness = 1;
int white_ratio_proba = 5;

int main()
{
	
	/* sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);
	
	cout << "if you want to execute first part click on k otherwise on D" << endl;

    while (window.isOpen())
    {
		*/
		/*Text text;
		Font font;

		if (!font.loadFromFile("Fonts/FontFile.ttf"))
		{
			std::cout << "Error loading file" << std::endl;

			system("pause");
		}
		text.setFont(font);
		text.setString("if you want to execute first part click on k otherwise on D");
		text.setCharacterSize(24); 
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		window.clear();
			window.draw(text);
			window.display();*/
		
	/*sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::K)
			{
				RectangleShape rect;
				window.clear();

				drawrectangle(100, rect, window);
				window.display();
				
			}
			if (event.key.code == sf::Keyboard::D)
			{
				window.clear();
				//a vector of vector that will contains all the vertex array needed to build my rectangles 
				vector<vector<Vector2f>> rectangle_list = { {Vector2f(origin+outline_thickness, origin+outline_thickness),Vector2f(width - origin-outline_thickness, origin+outline_thickness), Vector2f(width - origin-outline_thickness, height - origin-outline_thickness),Vector2f(origin+outline_thickness, height - origin-outline_thickness)} };
				//same as the previous one just bigger by a difference of the outline thickness 
				vector<vector<Vector2f>> outline_rectangle_list = { {Vector2f(origin, origin),Vector2f(width - origin, origin), Vector2f(width - origin, height - origin),Vector2f(origin, height - origin)} };


				for (int i = 0;i < subdivisions;i++) {
					//a random index to grab a random rectangle from the list
					int index = int(random(0, outline_rectangle_list.size()-1));
					vector<Vector2f> rect = outline_rectangle_list[index];
					//
					int rect_left_x = rect[0].x;
					int rect_right_x = rect[1].x;
					int rect_top_y = rect[0].y;
					int rect_bottom_y = rect[2].y;

					//random number between 0.5 and 1.5 used as the split ratio of the original rectangle
					float splitor_factor = randomreal(0.5, 1.5);
					//randomising the probability of the vertical and horizontal splits
					//horizontal split
					if (randomreal(0, 1) < 0.5) {
						// make sure that the width of the rectangle will be always bigger than the min_diff
						if ((rect_right_x - rect_left_x) > min_diff) {
							//the new x coordinate after splitting the rectangle
							int new_x = (rect_right_x - rect_left_x) / 2 * splitor_factor + rect_left_x;

							//erasing the original rectangle and adding the two new ones to the liste for both the rectangle and the outline of the rectangle
							rectangle_list.erase(rectangle_list.begin() + index);
							rectangle_list.push_back({ {Vector2f(rect_left_x + outline_thickness, rect_top_y + outline_thickness), Vector2f(new_x - outline_thickness, rect_top_y + outline_thickness), Vector2f(new_x - outline_thickness , rect_bottom_y - outline_thickness), Vector2f(rect_left_x + outline_thickness, rect_bottom_y - outline_thickness)} });
							rectangle_list.push_back({ {Vector2f(new_x + outline_thickness, rect_top_y + outline_thickness), Vector2f(rect_right_x - outline_thickness, rect_top_y + outline_thickness), Vector2f(rect_right_x - outline_thickness, rect_bottom_y - outline_thickness), Vector2f(new_x + outline_thickness, rect_bottom_y - outline_thickness)} });
							outline_rectangle_list.erase(outline_rectangle_list.begin() + index);
							outline_rectangle_list.push_back({ {Vector2f(rect_left_x, rect_top_y), Vector2f(new_x , rect_top_y), Vector2f(new_x  , rect_bottom_y), Vector2f(rect_left_x, rect_bottom_y)} });
							outline_rectangle_list.push_back({ {Vector2f(new_x , rect_top_y), Vector2f(rect_right_x, rect_top_y), Vector2f(rect_right_x, rect_bottom_y), Vector2f(new_x , rect_bottom_y)} });

						}

					}
					//vertical split
						else {
						// make sure that the height of the rectangle will be always bigger than the min_diff
							if ((rect_bottom_y - rect_top_y) > min_diff) {
								//the new y coordinate after splitting the rectangle
								int new_y = (rect_bottom_y - rect_top_y) / 2 * splitor_factor + rect_top_y;
								//erasing the original rectangle and adding the two new ones to the liste for both the rectangle and the outline of the rectangle
								rectangle_list.erase(rectangle_list.begin() + index);
								rectangle_list.push_back({ {Vector2f(rect_left_x + outline_thickness, rect_top_y + outline_thickness), Vector2f(rect_right_x - outline_thickness, rect_top_y + outline_thickness), Vector2f(rect_right_x - outline_thickness, new_y - outline_thickness), Vector2f(rect_left_x + outline_thickness, new_y - outline_thickness)} });
								rectangle_list.push_back({ {Vector2f(rect_left_x + outline_thickness, new_y + outline_thickness), Vector2f(rect_right_x - outline_thickness, new_y + outline_thickness),Vector2f(rect_right_x - outline_thickness, rect_bottom_y - outline_thickness), Vector2f(rect_left_x + outline_thickness, rect_bottom_y - outline_thickness)} });
								outline_rectangle_list.erase(outline_rectangle_list.begin() + index);
								outline_rectangle_list.push_back({ {Vector2f(rect_left_x, rect_top_y), Vector2f(rect_right_x, rect_top_y), Vector2f(rect_right_x, new_y - outline_thickness), Vector2f(rect_left_x, new_y - outline_thickness)} });
								outline_rectangle_list.push_back({ {Vector2f(rect_left_x, new_y), Vector2f(rect_right_x, new_y),Vector2f(rect_right_x, rect_bottom_y), Vector2f(rect_left_x, rect_bottom_y)} });
							}
						}

					//vertex array of the rectangle
					Vertex vertices[4];
					Vertex vertices_outline[4];

					//loop to create the rectangle 
					for (auto rectangle : rectangle_list) {
						int i = 0;
						Color color;
						//white retio
						if(random(0, white_ratio_proba)==0)
						{
							color = Color(random(0, 255), random(0, 255), random(0, 255));
						}
						else
						{
							color = Color::White;
						}
						
						for (auto vector : rectangle) {
							vertices[i] = Vertex(vector,color);
							i++;
						} 

					}
					//loop to create the outline rectangle 
					for (auto rectangle : outline_rectangle_list) {
						int i = 0;
						Color color = Color::Black;

						for (auto vector : rectangle) {
							vertices_outline[i] = Vertex(vector, color);
							i++;
						}
					}
					
					window.draw(vertices_outline, 4, Quads);
					window.draw(vertices, 4, Quads);
				}
				window.display();
				
			}
		}
	}
		
	
    }*/
/*game 1*/
/*srand(static_cast<unsigned>(time(NULL)));
Game game; 


while (game.getWindowIsOpen()&&!game.getEndGame())
{
	game.update();
	game.render();
} */ 
/*game 3*/
srand(time(static_cast<unsigned>(0)));
Game game;
game.run();
return 0;
}
	