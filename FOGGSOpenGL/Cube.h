#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	static int numVertices, numNormals, numIndices;

	Vector3 _position;
	Material* _material;
	int _mat;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, int material);
	~Cube();

	void Draw();
	void Update();
	void InitMaterial();
};

