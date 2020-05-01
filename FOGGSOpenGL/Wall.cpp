#include "Wall.h"
#include <iostream>
#include <fstream>

Wall::Wall(Mesh* mesh, Texture2D* texture, float x, float y, float z, int rotationAxis) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotationAxis = rotationAxis;
}

Wall::~Wall()
{
	delete _material;
}

void Wall::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		InitMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		switch (_rotationAxis)
		{
		case (1):
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			break;
		case (2):
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			break;
		default:
			glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
			break;
		}
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Wall::Update()
{
}

void Wall::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.5; _material->Ambient.y = 0.5; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.3; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}