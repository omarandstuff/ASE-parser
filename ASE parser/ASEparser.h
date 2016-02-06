#pragma once

#include "3Dmath.h"
#include <string>
#include <vector>
using namespace std;
using namespace Math3D;

#ifndef ASE_PARSER

namespace ASEParser
{
	// Main class for ASE files parsing.
	class Parser
	{
	public:
		Parser(wstring filename);
		~Parser();

	private:
		wstring m_fileName;
		unsigned int m_firstFrame;
		unsigned int m_lastFrame;
		unsigned int m_framespeed;
		unsigned int m_ticksPerFrame;
		Vector3 m_backgroundStatit;
		Vector3 m_ambientStatic;
		vector<Object> m_objects;
	};

	// Base class for a 3d entity.
	struct Object
	{
		wstring Name;
		Vector3 InheritPosition;
		Vector3 InheritRotaion;
		Vector3 InheritScale;
		Matrix4 TransformationMatrix;
		Vector3 RotationAxis;
		float RotationAngle;
		Vector3 Scale;
		Vector3 ScaleAxis;
		float ScaleAxisAngle;
	};

	// Vertex information about a vertex in a shape object.
	struct LineVertex
	{
		ShapeLine::VERTEX_KIND VertexKind;
		Vector3 Position;
	};

	// Grouo of vertex ina shape object.
	struct ShapeLine
	{
		enum VERTEX_KIND
		{
			KNOT,
			INTERPOLATION
		};
		vector<LineVertex> vertices;
	};

	// Inherit form a 3D object entity as shape of lines
	struct ShapeObject : public Object
	{
		vector<ShapeLine> lines;
	};
}

#endif // !ASE_PARSER
