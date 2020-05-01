#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, int material) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_mat = material;
}

Cube::~Cube()
{
	delete _material;
}

void Cube::Draw()
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
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update() {}

void Cube::InitMaterial()
{
	_material = new Material();
	if (_mat == 0) // Wood
	{
		_material->Ambient.x = 0.4; _material->Ambient.y = 0.4; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.8; _material->Diffuse.z = 0.6; _material->Diffuse.w = 1.0;
		_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
		_material->Shininess = 100.0f;
	}
	else if (_mat == 1) // Metal
	{
		_material->Ambient.x = 0.8; _material->Ambient.y = 0.8; _material->Ambient.z = 0.8; _material->Ambient.w = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.8; _material->Diffuse.z = 0.8; _material->Diffuse.w = 1.0;
		_material->Specular.x = 5.0; _material->Specular.y = 5.0; _material->Specular.z = 5.0; _material->Specular.w = 1.0;
		_material->Shininess = 100.0f;
	}
	else if (_mat == 2) // Paper
	{
		_material->Ambient.x = 0.8; _material->Ambient.y = 0.7; _material->Ambient.z = 0.2; _material->Ambient.w = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.75; _material->Diffuse.z = 0.7; _material->Diffuse.w = 1.0;
		_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
		_material->Shininess = 100.0f;
	}
	else if (_mat == 3) // Door
	{
		_material->Ambient.x = 0.8; _material->Ambient.y = 0.8; _material->Ambient.z = 0.8; _material->Ambient.w = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.8; _material->Diffuse.z = 0.6; _material->Diffuse.w = 1.0;
		_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
		_material->Shininess = 100.0f;
	}
}