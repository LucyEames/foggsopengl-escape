#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Wall : public SceneObject
{
private:
	static int numVertices, numNormals, numIndices;

	Vector3 _position;
	int _rotationAxis;
	Material* _material;

public:
	Wall(Mesh* mesh, Texture2D* texture, float x, float y, float z, int rotationAxis);
	~Wall();

	void Draw();
	void Update();
	void InitMaterial();
};

