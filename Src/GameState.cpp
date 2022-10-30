#include "GameState.h"
#include <math.h>
#include <iostream>
GameState::GameState(Shader& shader)
	:
	shader(shader),
	//player(1.0f, 72.0f, 60.0f, 60.0f), 
	box(0.0f, 0.0f, 64.0f, 64.0f),
	backgroundTexture("Assets/Background/Green.png"),
	grassTexture("Assets/Tiles/GrassTile.png"),
	playerTexture("Assets/Virtual Guy/a_Player.png"),
	pigTexture("Assets/Enemies/AngryPig/a_Pig.png"),
	appleTexture("Assets/Items/Fruits/Apple.png"),
	orangeTexture("Assets/Items/Fruits/Orange.png"),
	angryBlockTexture("Assets/Traps/Rock Head/AngryBlock.png"),
	slimeTexture("Assets/Enemies/Slime/a_Slime.png"),
	trophyTexture("Assets/Items/Checkpoints/End/Trophy.png"),
	buttonTexture("Assets/Menu/Buttons/Play.png")
{

	shader.setUniform1i("u_textures[0]", 0);
	shader.setUniform1i("u_textures[1]", 1);
	shader.setUniform1i("u_textures[2]", 2);
	shader.setUniform1i("u_textures[3]", 3);
	shader.setUniform1i("u_textures[4]", 4);
	shader.setUniform1i("u_textures[5]", 5);
	shader.setUniform1i("u_textures[6]", 6);
	shader.setUniform1i("u_textures[7]", 7);
	shader.setUniform1i("u_textures[15]", 15);


	shader.setUniform1f("facing_right", 1.0f);
}

void GameState::set_game_state(unsigned int state)
	
{
	current_state = state;
}

void GameState::load_state()
{
	if (current_state == 0)
		load_main_menu();
	if (current_state == 1)
		load_level_1();
	if (current_state == 2)
		load_level_2();
}
void GameState::load_main_menu()
{
	
	c_level.init_level_layout(menu);
	v_Buttons.push_back(Button(448.0f, 320.0f, 128.0f, 128.0f));
	player_ptr = std::make_shared<Player>(475.0f, 150.0f, 60.0f, 60.0f);

	// Load Background
	glActiveTexture(GL_TEXTURE0);
	init_vertices(box, VAOBackground, backgroundVert, 0.0f, 704.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	backgroundTexture.init();
	backgroundTexture.setVertAttribs(1, 2, 5, 3);

	// Player
	init_vertices(*player_ptr, VAOPlayer, playerVert, 0.0f, 0.0f, 0.0104f, 0.67f, 0.0625f, 0.28f);
	glActiveTexture(GL_TEXTURE1);
	playerTexture.init();
	playerTexture.setVertAttribs(1, 2, 5, 3);

	// Play Button
	glActiveTexture(GL_TEXTURE5);
	init_vertices(v_Buttons[0], VAOButton, buttonVert, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	buttonTexture.init();
	buttonTexture.setVertAttribs(1, 2, 5, 3);

	
}

void GameState::load_level_1()
{
	player_ptr = std::make_shared<Player>(1.0f, 72.0f, 60.0f, 60.0f);
	trophy_ptr = std::make_shared<Trophy>(868.0f, 450.0f, 120.0f, 120.0f);

	c_level.init_level_layout(level1);
	v_Slimes.push_back(Slime(300.0f, 64.0f, 93.87, 64.0f, true));
	for (int i = 0; i < 10; i++) {
		v_Oranges.push_back(Fruit(400 + i * 44.04, 64.0f, 44.0f, 44.0f)); fruit_count++;
	}
	for (int i = 0; i < 7; i++) {
		v_Oranges.push_back(Fruit(390.0f + i * 44.04, 450.0f, 44.0f, 44.0f)); fruit_count++;
	}
	
	// Load Background
	init_vertices(box, VAOBackground, backgroundVert, 0.0f, 704.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	backgroundTexture.init();
	backgroundTexture.setVertAttribs(1, 2, 5, 3);

	// Load Grass Tiles
	init_vertices(box, VAOGrass, grassVert, 0.0f, 704.0f, 0.1, 0.0f, .80f, 1.0f);
	grassTexture.init();
	grassTexture.setVertAttribs(1, 2, 5, 3);

	// Load Player
	init_vertices(*player_ptr, VAOPlayer, playerVert, 0.0f, 0.0f, 0.0104f, 0.67f, 0.0625f, 0.28f);
	playerTexture.init();
	playerTexture.setVertAttribs(1, 2, 5, 3);

	// Oranges
	init_vertices(v_Oranges[0], VAOOrange, orangeVert, 0.0f, 0.0f, 0.00925f, 0.2222f, 0.039f, 0.625f);
	orangeTexture.init();
	orangeTexture.setVertAttribs(1, 2, 5, 3);

	// Load Slimes
	init_vertices(v_Slimes[0], VAOSlime, slimeVert, 0.0f, 0.0f, 0.0f, 0.0f, 0.1, 1.0f);
	slimeTexture.init();
	slimeTexture.setVertAttribs(1, 2, 5, 3);

	// Load Trophy
	init_vertices(*trophy_ptr, VAOTrophy, trophyVert, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	trophyTexture.init();
	trophyTexture.setVertAttribs(1, 2, 5, 3);

	backgroundTexture.bind();
	playerTexture.bind(1);
	grassTexture.bind(4);
	orangeTexture.bind(5);
	angryBlockTexture.bind(6);
	slimeTexture.bind(7);
	trophyTexture.bind(15);
}
void GameState::load_level_2()
{
	player_ptr = std::make_shared<Player>(1.0f, 72.0f, 60.0f, 60.0f);
	c_level.init_level_layout(level2);
	trophy_ptr = std::make_shared<Trophy>(995, 640.0f, 120.0f, 120.0f);
	v_AngryBlocks.push_back(AngryBlock(320.0f, 200.0f, 98.0f, 98.0f));
	v_AngryBlocks.push_back(AngryBlock(64.0f, 170.0f, 98.0f, 98.0f, 14.0f, 24.0f));

	v_Apples.push_back(Fruit(1212.0f, 450, 72.0f, 72.0f));
	fruit_count++;
	for (int i = 0; i < 9; i++)
	{
		v_Oranges.push_back(Fruit(380.0f + 44 * i, 640.0f, 44.0f, 44.0f));
		fruit_count++;
	}
	for (int i = 1; i < 20; i++)
	{
		v_Oranges.push_back(Fruit(200.0f + 50.0f * i, 64.0f, 44.0f, 44.0f));
		fruit_count++;
	}
	for (int i = 0; i < 5; i++) {
		v_Oranges.push_back(Fruit(76.0f, 280.0f + 44.0f * i, 44.0f, 44.0f));
		fruit_count++;
	}
	for (int i = 1; i < 9; i++)
	{
		float x = 36 - 36 * i;
		float y = sqrt((256*256 - (x*x)));
		
		v_Oranges.push_back(Fruit(330.0f + x, 490.0f + y, 44.0f, 44.0f));
		fruit_count++;
	}
	//for (int i = 0; i < 5; i++) v_Oranges.push_back(Fruit(100.0f + 44.0f * i, 640.0f + 10.0f * i, 44.0f, 44.0f));
	v_Pigs.push_back(Pig(750.0f, 64.0f, 96.0f, 80.0f));

	// Load Background
	init_vertices(box, VAOBackground, backgroundVert, 0.0f, 704.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	backgroundTexture.init();
	backgroundTexture.setVertAttribs(1, 2, 5, 3);

	// Load Grass Tiles
	init_vertices(box, VAOGrass, grassVert, 0.0f, 704.0f, 0.1, 0.0f, .80f, 1.0f);
	grassTexture.init();
	grassTexture.setVertAttribs(1, 2, 5, 3);

	// Load Player
	init_vertices(*player_ptr, VAOPlayer, playerVert, 0.0f, 0.0f, 0.0104f, 0.67f, 0.0625f, 0.28f);
	playerTexture.init();
	playerTexture.setVertAttribs(1, 2, 5, 3);

	// Load Fruits
	init_vertices(v_Apples[0], VAOApple, appleVert, 0.0f, 0.0f, 0.00925f, 0.2222f, 0.039f, 0.625f);
	appleTexture.init();
	appleTexture.setVertAttribs(1, 2, 5, 3);


	// Oranges
	init_vertices(v_Oranges[0], VAOOrange, orangeVert, 0.0f, 0.0f, 0.00925f, 0.2222f, 0.039f, 0.625f);
	orangeTexture.init();
	orangeTexture.setVertAttribs(1, 2, 5, 3);

	// Load Pigs
	init_vertices(v_Pigs[0], VAOPig, pigVert, 0.1f, 0.0f, 0.0035, 0.5f, 0.05729f, 0.25f);
	pigTexture.init();
	pigTexture.setVertAttribs(1, 2, 5, 3);

	// Angry Block
	init_vertices(v_AngryBlocks[0], VAOABlock, aBlockVert, 0.0f, 0.0f, 0.0238095, 0.11905, 0.15238 , 0.7619);
	angryBlockTexture.init();
	angryBlockTexture.setVertAttribs(1, 2, 5, 3);
	
	// Load Trophy
	init_vertices(*trophy_ptr, VAOTrophy, trophyVert, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	trophyTexture.init();
	trophyTexture.setVertAttribs(1, 2, 5, 3);

	backgroundTexture.bind();
	playerTexture.bind(1);
	pigTexture.bind(2);
	appleTexture.bind(3);
	grassTexture.bind(4);	
	orangeTexture.bind(5);
	angryBlockTexture.bind(6);
	trophyTexture.bind(15);
}


void GameState::load_game_over()
{

}

void GameState::init_vertices(Entity& entity, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, entity.getWidth(), entity.getHeight(), tex_left, tex_bottom, tex_width, tex_height);
	e_VAO.init(vert, 20, indices, 6);
	e_VAO.setVertexAttribPointersf(0, 3, 5, 0);
	// VAO Layout location
	// 3 coordinates, so size of 3 per attributes
	// Total of 5 values (plus the texture) so 5 as stride
	// 0 Offset to begn vertex coords
}
void GameState::init_vertices(Fruit& fruit, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, fruit.getWidth(), fruit.getHeight(), tex_left, tex_bottom, tex_width, tex_height);
	e_VAO.init(vert, 20, indices, 6);
	e_VAO.setVertexAttribPointersf(0, 3, 5, 0);
};

void GameState::init_vertices(Button& b, VertexArray& b_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, b.getWidth(), b.getHeight(), tex_left, tex_bottom, tex_width, tex_height);
	b_VAO.init(vert, 20, indices, 6);
	b_VAO.setVertexAttribPointersf(0, 3, 5, 0);
}

