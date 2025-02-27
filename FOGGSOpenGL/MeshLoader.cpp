#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);


		return mesh;
	}

	//Mesh* MeshLoader::LoadObj(char* path)
	//{
	//	Mesh* mesh = new Mesh();
	//	std::vector <Vector3> out_vertices;
	//	std::vector <Vector2> out_uvs;
	//	std::vector <Vector3> out_normals;

	//	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	//	std::vector <Vector3> temp_vertices;
	//	std::vector <Vector2> temp_uvs;
	//	std::vector <Vector3> temp_normals;

	//	ifstream inFile;
	//	inFile.open(path);

	//	if (!inFile.good())
	//	{
	//		cerr << "Can't open .obj file " << path << endl;
	//		return nullptr;
	//	}

	//	
	//	//LoadObjVertices(inFile, *mesh);
	//	//LoadObjTexCoords(inFile, *mesh);
	//	//LoadObjNormals(inFile, *mesh);
	//	//LoadObjIndices(inFile, *mesh);

	//	return mesh;
	//}
}