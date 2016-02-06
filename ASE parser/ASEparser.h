#pragma once

#include "3Dmath.h"
#include <string>
using namespace std;

#ifndef ASE_PARSER

namespace ASEParser
{
	class Object
	{

	};

	class ASEParser
	{
	public:
		ASEParser(wstring filename);
		~ASEParser();

	private:
		wstring m_fileName;
		unsigned int m_firstFrame;
		unsigned int m_lastFrame;
		unsigned int m_framespeed;
		unsigned int m_ticksPerFrame;
		Vector3 m_backgroundStatit;
		Vector3 m_ambientStatic;
	};
}



#endif // !ASE_PARSER
