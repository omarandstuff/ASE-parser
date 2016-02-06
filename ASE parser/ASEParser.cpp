#include "ASEparser.h"
using namespace ASEParser;

Parser::Parser(wstring filename)
{
	Parse(filename);
}

Parser::~Parser()
{

}

void Parser::Parse(wstring filename)
{
	if (filename == L"") // Do not parse a empty filename.
	{
#if ASE_VERBOSE
		wcout << "ASEParser: Wrong filename." << endl;
#endif
		return;
	}

	// Get track of the filename.
	m_fileName = filename;

	// 
	wfstream wStream((filename).c_str());

	if (!wStream) // Do not parse a file that does not exist.
	{
#if ASE_VERBOSE
		wcout << "ASEParser: The file " << filename << " does not exist." << endl;
#endif
		return;
	}

	// Do work until reach all the content
	wchar_t line[256];
	while (wStream.getline(line, 256))
	{
		// Line that can be accessed element by element.
		wistringstream* newLine = new wistringstream(line, wistringstream::in);

		wstring lineElement;

		// Get the first line element.
		*newLine >> lineElement;

		if (lineElement == L"*SCENE") // Scene basic information.
		{
			m_originFilename = L"";

			do // Iterate all the anidated lines in the scene block.
			{
				// Line in scene block.
				wStream.getline(line, 256);
				delete newLine; newLine = new wistringstream(line, wistringstream::in);

				// Get the first line element.
				*newLine >> lineElement;

				if (lineElement == L"*SCENE_FILENAME") // Origin filename (original file taht was exported to ASE)
				{
					// Extract the string
					*newLine >> lineElement;
					m_originFilename = lineElement;
					while (lineElement.back() != L'\"')
					{
						*newLine >> lineElement;
						m_originFilename += L" " + lineElement;
					}
					m_originFilename = m_originFilename.substr(1, m_originFilename.size() - 2);
				}
			} while (lineElement != L"}");
		}

		// Delete teh stream object.
		delete newLine;
	}
}