#include "GameState.h"

GameState::GameState(Shader& shader)
	:
	shader(shader),
	player(1.0f, 200.0f, 60.0f, 60.0f), 
	box(0.0f, 0.0f, 64.0f, 64.0f),
	backgroundTexture("Assets/Background/Green.png"),
	grassTexture("Assets/Tiles/GrassTile.png"),
	playerTexture("Assets/Virtual Guy/a_Player.png"),
	pigTexture("Assets/Enemies/AngryPig/a_Pig.png"),
	appleTexture("Assets/Items/Fruits/Apple.png"),
	orangeTexture("Assets/Items/Fruits/Orange.png"),
	angryBlockTexture("Assets/Traps/Rock Head/AngryBlock.png")
{

	shader.setUniform1i("u_textures[0]", 0);
	shader.setUniform1i("u_textures[1]", 1);
	shader.setUniform1i("u_textures[2]", 2);
	shader.setUniform1i("u_textures[3]", 3);
	shader.setUniform1i("u_textures[4]", 4);
	shader.setUniform1i("u_textures[5]", 5);
	shader.setUniform1i("u_textures[6]", 6);
	shader.setUniform1i("u_textures[7]", 7);
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
}


void GameState::load_main_menu()
{
	// Play Button
	v_Buttons.push_back(Button(448.0f, 320.0f, 128.0f, 128.0f, "Assets/Menu/Buttons/Play.png"));
	v_VAOButtons.push_back(VertexArray());
	init_vertices(v_Buttons[0], v_VAOButtons[0], buttonVert, v_Buttons[0].getX(), v_Buttons[0].getY(), 0.0f, 0.0f, 1.0f, 1.0f);
	v_Buttons[0].get_texture().init();
	v_Buttons[0].get_texture().setVertAttribs(1, 2, 5, 3);

	v_Buttons[0].get_texture().bind();
}
void GameState::load_level_1()
{
	
	c_level.init_level_layout(level1);

	v_AngryBlocks.push_back(AngryBlock(320.0f, 200.0f, 98.0f, 98.0f));
	v_Apples.push_back(Fruit(1212.0f, 450, 72.0f, 72.0f));
	//v_Apples.push_back(Fruit(200.0f, 450.0f, 72.0f, 72.0f));
	//v_Apples.push_back(Fruit(500.0f, 64.0f, 72.0f, 72.0f));
	
	for (int i = 1; i < 20; i++)
	{
		v_Oranges.push_back(Fruit(200.0f + 50.0f * i, 64.0f, 44.0f, 44.0f));
	}
	for (int i = 0; i < 4; i++) v_Oranges.push_back(Fruit(44.0f * i, 640.0f, 44.0f, 44.0f));
	for (int i = 0; i < 10; i++) v_Oranges.push_back(Fruit(210.0f, 256.0f + 44.0f * i, 44.0f, 44.0f));
	for (int i = 1; i < 5; i++) v_Oranges.push_back(Fruit(910.0f + 50.0f * i, 320.0f, 44.0f, 44.0f));
	v_Pigs.push_back(Pig(750.0f, 64.0f, 96.0f, 80.0f));
	//v_Pigs.push_back(Pig(954.0f, 320.0f, 96.0f, 80.0f, 150.0f));
	//v_Pigs.push_back(Pig(300.0f, 450.0f, 96.0f, 80.0f, 800.0f));k
	

	// Load Background
	init_vertices(box, VAOBackground, backgroundVert, 0.0f, 704.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	backgroundTexture.init();
	backgroundTexture.setVertAttribs(1, 2, 5, 3);

	// Load Grass Tiles
	init_vertices(box, VAOGrass, grassVert, 0.0f, 704.0f, 0.1, 0.0f, .80f, 1.0f);
	grassTexture.init();
	grassTexture.setVertAttribs(1, 2, 5, 3);

	// Load Player
	init_vertices(player, VAOPlayer, playerVert, 0.0f, 0.0f, 0.0104f, 0.67f, 0.0625f, 0.28f);
	playerTexture.init();
	playerTexture.setVertAttribs(1, 2, 5, 3);

	// Load Fruits
	//  init_vertices(v_Apples[0], VAOApple, appleVert, v_Apples[0].getX(), v_Apples[0].getY(), 0.00925f, 0.2222f, 0.039f, 0.625f);
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
	
	backgroundTexture.bind();
	playerTexture.bind(1);
	pigTexture.bind(2);
	appleTexture.bind(3);
	grassTexture.bind(4);	
	orangeTexture.bind(5);
	angryBlockTexture.bind(6);
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

