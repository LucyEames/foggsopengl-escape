#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Fan : public SceneObject
{
private:
	static int numVertices, numNormals, numIndices;

	Vector3 _position;
	GLfloat _rotation;
	float _rotationSpeed;
	Material* _material;

public:
	Fan(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rotation);
	~Fan();

	void Draw();
	void Update();
	void InitMaterial();
};

