#pragma once

#include "3Dmath.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace Math3D;

#ifndef ASE_PARSER

#define ASE_VERBOSE true

namespace ASEParser
{
	struct Object;
	struct LineVertex;
	struct ShapeLine;
	struct ShapeObject;

	// Main class for ASE files parsing.
	class Parser
	{
	public:
		Parser(wstring filename);
		~Parser();

		// Parse form a file in disk.
		void Parse(wstring filename);

		// Sacale every vertex in objects.
		void Scale(double value);

		// Translate every vertex in obects.
		void Translate(double x, double y, double z);

	public:
		wstring m_fileName;
		wstring m_originFilename;
		unsigned int m_firstFrame;
		unsigned int m_lastFrame;
		unsigned int m_framespeed;
		unsigned int m_ticksPerFrame;
		Vector3 m_backgroundStatic;
		Vector3 m_ambientStatic;
		vector<ShapeObject> m_shapeObjects;
	};

	// Base class for a 3d entity.
	struct Object
	{
		wstring Name;
		Vector3 InheritPosition;
		Vector3 InheritRotaion;
		Vector3 InheritScale;
		Matrix4 TransformationMatrix;
		Vector3 Position;
		Vector3 RotationAxis;
		float RotationAngle;
		Vector3 Scale;
		Vector3 ScaleAxis;
		float ScaleAxisAngle;
	};

	// Vertex information about a vertex in a shape object.
	struct LineVertex
	{
		enum VERTEX_KIND
		{
			KNOT,
			INTERPOLATION
		};
		VERTEX_KIND VertexKind;
		Vector3 Position;
	};

	// Grouo of vertex ina shape object.
	struct ShapeLine
	{
		vector<LineVertex> vertices;
	};

	// Inherit form a 3D object entity as shape of lines
	struct ShapeObject : public Object
	{
		vector<ShapeLine> lines;
	};
}

#endif // !ASE_PARSER
