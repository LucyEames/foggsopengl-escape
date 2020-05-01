#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include "MeshLoader.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));

	InitGL(argc, argv);
	InitLighting();
	InitObjects();

	// Main Loop
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	delete room;
	delete objects;
	delete _lightPosition;
	delete _lightData;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // this clears the scene
	Vector3 v = { 0.0f, 0.5f, 1.0f };
	Vector3 v1 = { camViewpoints[cameraViewI][cameraViewJ].x, camViewpoints[cameraViewI][cameraViewJ].y + (((v1.x * v1.x) / 100.0f) * 0.1f) + 3.5f, camViewpoints[cameraViewI][cameraViewJ].z * 0.6f};
	Vector3 v2 = { camViewpoints[cameraViewI][cameraViewJ+1].x, camViewpoints[cameraViewI][cameraViewJ+1].y, camViewpoints[cameraViewI][cameraViewJ+1].z};
	Color c = { 1.0f, 0.0f, 1.0f };

	if (startCheck)
	{
		DrawString("ESCAPE\n\n'A' AND 'D' TO TURN\n'W' TO LOOK CLOSER\n'S' TO BACK UP\n'C' TO CHECK\nPRESS B TO BEGIN", &v, &c);
	}
	else if (pauseCheck)
	{
		if (cameraViewJ == 0)
			DrawString("PAUSE\n\nPRESS X TO EXIT", &v1, &c);
		else
			DrawString("PAUSE\n\nPRESS X TO EXIT", &v2, &c);
	}
	else if (doorUnlocked)
	{
		DrawString("YOU ESCAPED THE LOCKED ROOM!", &v2, &c);
	}
	else
	{
		if (itemCheck)
		{
			if (cameraViewI == 0)
			{
				if (!keyTaken)
				{
					DrawString(checkInfo[2][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
				}
				else
				{
					DrawString(checkInfo[3][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
				}
			}
			if (cameraViewI == 1)
			{
				if (!paperTaken)
				{
					DrawString(checkInfo[0][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
				}
				else
				{
					DrawString(checkInfo[1][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
				}
			}
			if (cameraViewI == 2)
			{
				if (!safeOpen)
				{
					doingLock = true;
					if (doingLock)
					{
						for (int i = 0; i < 3; i++)
						{
							Vector3 v3 = { camViewpoints[cameraViewI][2].x, camViewpoints[cameraViewI][2].y, camViewpoints[cameraViewI][2].z + i/2.0f };
							DrawString(numbers[lockCombo[i]], &v3, &c);
						}
					}
				}
				else
				{
					if (!keyTaken)
					{
						DrawString(checkInfo[4][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
					}
					else
					{
						DrawString(checkInfo[5][checkInfoPointer], &camViewpoints[cameraViewI][2], &c);
					}
				}
			}
		}
	}
	
	int objectsTotal = 6;
	if (paperTaken)
		objectsTotal = 5;

	for (int i = 0; i < objectsTotal; i++)
	{
		objects[i]->Draw();
	}
	for (int i = 0; i < 6; i++)
	{
		room[i]->Draw();
	}

	glFlush(); // flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	for (int i = 0; i < 6; i++)
	{
		objects[i]->Update();
	}

	glutPostRedisplay();

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (startCheck)
	{
		if (key == 'b')
		{
			startCheck = false;
		}
		if (key == 'x')
		{
			glutLeaveMainLoop();
		}
	}
	else
	{
		if (key == 'p')
		{
			pauseCheck = !pauseCheck;
		}
		if (pauseCheck || doorUnlocked)
		{
			if (key == 'x')
			{
				glutLeaveMainLoop();
			}
		}
		else
		{
			if (cameraViewJ == 0)
			{
				if (key == 'd')
				{
					cameraViewI -= 1;
					if (cameraViewI < 0)
						cameraViewI = 2;
					camera->center = camViewpoints[cameraViewI][cameraViewJ];
				}
				if (key == 'a')
				{
					cameraViewI += 1;
					if (cameraViewI > 2)
						cameraViewI = 0;
					camera->center = camViewpoints[cameraViewI][cameraViewJ];
				}
				if (key == 'w')
				{
					cameraViewJ = 1;
					camera->eye = camViewpoints[cameraViewI][cameraViewJ];
				}
			}
			else
			{
				if (doingLock)
				{
					if (key == 'd')
					{
						lockPointer += 1;
						if (lockPointer > 2)
							lockPointer = 0;
					}
					if (key == 'a')
					{
						lockPointer -= 1;
						if (lockPointer < 0)
							lockPointer = 2;
					}
					if (key == 'w')
					{
						lockCombo[lockPointer] += 1;
						if (lockCombo[lockPointer] > 9)
							lockCombo[lockPointer] = 0;
					}
					if (key == 'c')
					{
						if (lockCombo[0] == 5 && lockCombo[1] == 2 && lockCombo[2] == 8)
						{
							safeOpen = true;
							doingLock = false;
							checkInfoPointer = 0;
						}
					}
					if (key == 's')
					{
						doingLock = false;
						itemCheck = false;
					}
				}
				else
				{
					if (key == 'c')
					{
						checkInfoPointer += 1;
						if (checkInfoPointer > 2)
						{
							if (cameraViewI == 1)
							{
								paperTaken = true;
							}
							if (safeOpen)
							{
								keyTaken = true;
							}
							if (cameraViewI == 0 && keyTaken)
							{
								doorUnlocked = true;
							}
							checkInfoPointer = 0;
						}
						itemCheck = true;
					}
					if (key == 's')
					{
						cameraViewJ = 0;
						camera->eye = { 0.0f, 2.0f, 10.0f };
						itemCheck = false;
						checkInfoPointer = 0;
					}
				}
			}
		}
	}
}

void HelloGL::InitObjects()
{
	// Variable initialisation
	rotation = 0.0f;
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 2.0f; camera->eye.z = 10.0f;
	camera->center.x = 0.0f; camera->center.y = 1.0f; camera->center.z = -19.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* safeMesh = MeshLoader::Load((char*)"bigcube.txt");
	Mesh* wallMesh = MeshLoader::Load((char*)"wall.txt");
	Mesh* doorMesh = MeshLoader::Load((char*)"door.txt");
	Mesh* tableMesh = MeshLoader::Load((char*)"table.txt");
	Mesh* fanMesh = MeshLoader::Load((char*)"fan.txt");
	Texture2D* woodTexture = new Texture2D();
	Texture2D* safeTexture = new Texture2D();
	Texture2D* doorTexture = new Texture2D();
	Texture2D* paperTexture = new Texture2D();
	woodTexture->Load((char*)"wood.bmp", 640, 640);
	safeTexture->Load((char*)"safe.bmp", 1378, 1378);
	doorTexture->Load((char*)"door.bmp", 844, 1526);
	paperTexture->Load((char*)"paper.bmp", 816, 612);

	objects[0] = new Cube(tableMesh, woodTexture, -15.0f, -1.0f, -8.0f, 0);
	objects[1] = new Cube(safeMesh, safeTexture, 13.0f, 0.0f, 0.0f, 1);
	objects[2] = new Cube(doorMesh, doorTexture, 0.0f, 2.0f, -19.0f, 3);
	objects[3] = new Fan(fanMesh, woodTexture, 0.0f, 9.5f, -4.0f, 0.0f);
	objects[4] = new Fan(fanMesh, woodTexture, 0.0f, 9.5f, -4.0f, 90.0f);
	objects[5] = new Cube(cubeMesh, paperTexture, -15.0f, -0.9f, -8.0f, 2);

	room[0] = new Wall(wallMesh, woodTexture, 0.0f, -3.0f, 0.0f, 0);//floor
	room[1] = new Wall(wallMesh, woodTexture, -20.0f, -3.0f, 0.0f, 2);
	room[2] = new Wall(wallMesh, woodTexture, 20.0f, -3.0f, 0.0f, 2);
	room[3] = new Wall(wallMesh, woodTexture, 0.0f, -3.0f, -20.0f, 1);
	room[4] = new Wall(wallMesh, woodTexture, 0.0f, -3.0f, 20.0f, 1);
	room[5] = new Wall(wallMesh, woodTexture, 0.0f, 10.0f, 0.0f, 0);//roof

}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 8.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.5;
	_lightData->Ambient.y = 0.5;
	_lightData->Ambient.z = 0.6;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.6;
	_lightData->Diffuse.y = 0.6;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	// Functions
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // z buffer
	glutInitWindowSize(800, 800);
	glutCreateWindow("FOGGS OpenGL - Escape");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	// Camera Functions
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800); // set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 1000); // set the correct persepective
	glMatrixMode(GL_MODELVIEW);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); // z buffer

	// Backface Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}