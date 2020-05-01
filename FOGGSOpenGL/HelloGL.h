#pragma once
#include <Windows.h> // Required for OpenGL on Windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL\freeglut.h" // freeglut library
#include "Structures.h"
#include "Cube.h"
#include "Wall.h"
#include "Fan.h"

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);
	void DrawString(const char* text, Vector3* position, Color* color);
private:
	float rotation;
	bool startCheck = true;
	bool pauseCheck;
	bool itemCheck;
	bool paperTaken;
	bool safeOpen;
	bool keyTaken;
	bool doorUnlocked;
	bool doingLock;
	int lockPointer;
	int lockCombo[3];
	int checkInfoPointer;
	int cameraViewI, cameraViewJ;
	
	Camera* camera;
	SceneObject* room[6];
	SceneObject* objects[6];
	Vector4* _lightPosition;
	Lighting* _lightData;
	
	const char* numbers[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	const char* checkInfo[6][3] = {
		{"", "There's a paper on the table with the code 528.", "You take the paper."},
		{"", "It's a table.", "There's nothing there."},
		{"", "It's the only door in the room.", "It's locked."},
		{"", "It's the only door in the room.", "You used the key. The door is open."},
		{"", "The safe is open. There's a key inside.", "You take the key."},
		{"", "The safe is open.", "There's nothing inside."} };
	Vector3 camViewpoints[3][3] = { {
		{ 0.0f, 1.0f, -19.0f }, { 0.0f, 1.0f, -4.0f }, { -2.0f, 1.0f, -14.0f } }, // normal view, zoomed view, text view
		{ { -15.0f, 1.0f, -8.0f }, { -8.8f, 3.8f, -4.0f }, { -15.0f, 1.3f, -6.0f } },
		{ { 10.0f, 1.0f, 0.0f }, { 2.1f, 1.0f, 0.4f },	{ 10.0f, 2.0f, -0.4f } } };
};

