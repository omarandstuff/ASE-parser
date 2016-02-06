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
				else if (lineElement == L"*SCENE_FIRSTFRAME") // Which frame starts the animation.
				{
					*newLine >> m_firstFrame;
				}
				else if (lineElement == L"*SCENE_LASTFRAME") // Which frame ends the animation.
				{
					*newLine >> m_lastFrame;
				}
				else if (lineElement == L"*SCENE_FRAMESPEED") // Animation frames per second.
				{
					*newLine >> m_framespeed;
				}
				else if (lineElement == L"*SCENE_TICKSPERFRAME") // Animation ticks per frame.
				{
					*newLine >> m_ticksPerFrame;
				}
				else if (lineElement == L"*SCENE_BACKGROUND_STATIC") // Backgroud color.
				{
					*newLine >> m_backgroundStatic.x;
					*newLine >> m_backgroundStatic.y;
					*newLine >> m_backgroundStatic.z;
				}
				else if (lineElement == L"*SCENE_AMBIENT_STATIC") // Ambient color.
				{
					*newLine >> m_ambientStatic.x;
					*newLine >> m_ambientStatic.y;
					*newLine >> m_ambientStatic.z;
				}
			} while (lineElement != L"}");
		}
		else if (lineElement == L"*SHAPEOBJECT") // Shape object in the hierarchy.
		{
			// Insert new shape object.
			m_shapeObjects.push_back(ShapeObject());
			ShapeObject* lastObject = &m_shapeObjects.back();

			do // Iterate all the anidated lines in the shape object block.
			{
				// Line in shape object block.
				wStream.getline(line, 256);
				delete newLine; newLine = new wistringstream(line, wistringstream::in);

				// Get the first line element.
				*newLine >> lineElement;

				if (lineElement == L"*NODE_NAME") // Object's name.
				{
					*newLine >> lastObject->Name;
				}
				else if (lineElement == L"*NODE_TM") // Trasformation data.
				{
					do // Iterate all the anidated lines in the TM block.
					{
						// Line in TM block.
						wStream.getline(line, 256);
						delete newLine; newLine = new wistringstream(line, wistringstream::in);

						// Get the first line element.
						*newLine >> lineElement;

						if (lineElement == L"*NODE_NAME") // Object's name.
						{
							*newLine >> lastObject->Name;
						}
						else if (lineElement == L"*INHERIT_POS") // Position inherited.
						{
							*newLine >> lastObject->InheritPosition.x;
							*newLine >> lastObject->InheritPosition.y;
							*newLine >> lastObject->InheritPosition.z;
						}
						else if (lineElement == L"*INHERIT_ROT") // Rotation inherited.
						{
							*newLine >> lastObject->InheritRotaion.x;
							*newLine >> lastObject->InheritRotaion.y;
							*newLine >> lastObject->InheritRotaion.z;
						}
						else if (lineElement == L"*INHERIT_SCL") // Scale inherited.
						{
							*newLine >> lastObject->InheritScale.x;
							*newLine >> lastObject->InheritScale.y;
							*newLine >> lastObject->InheritScale.z;
						}
						else if (lineElement == L"*INHERIT_SCL") // Scale inherited.
						{
							*newLine >> lastObject->InheritScale.x;
							*newLine >> lastObject->InheritScale.y;
							*newLine >> lastObject->InheritScale.z;
						}
						else if (lineElement == L"*TM_ROW0") // Transform matrix row 0.
						{
							*newLine >> lastObject->TransformationMatrix._00;
							*newLine >> lastObject->TransformationMatrix._01;
							*newLine >> lastObject->TransformationMatrix._02;
						}
						else if (lineElement == L"*TM_ROW1") // Transform matrix row 1.
						{
							*newLine >> lastObject->TransformationMatrix._10;
							*newLine >> lastObject->TransformationMatrix._11;
							*newLine >> lastObject->TransformationMatrix._12;
						}
						else if (lineElement == L"*TM_ROW2") // Transform matrix row 2.
						{
							*newLine >> lastObject->TransformationMatrix._20;
							*newLine >> lastObject->TransformationMatrix._21;
							*newLine >> lastObject->TransformationMatrix._22;
						}
						else if (lineElement == L"*TM_ROW3") // Transform matrix row 3.
						{
							*newLine >> lastObject->TransformationMatrix._30;
							*newLine >> lastObject->TransformationMatrix._31;
							*newLine >> lastObject->TransformationMatrix._32;
						}
						else if (lineElement == L"*TM_ROTAXIS") // Transform rotation axis.
						{
							*newLine >> lastObject->RotationAxis.x;
							*newLine >> lastObject->RotationAxis.y;
							*newLine >> lastObject->RotationAxis.z;
						}
						else if (lineElement == L"*TM_ROTANGLE") // Transform rotation angle.
						{
							*newLine >> lastObject->RotationAngle;
						}
						else if (lineElement == L"*TM_SCALE") // Transform scale.
						{
							*newLine >> lastObject->Scale.x;
							*newLine >> lastObject->Scale.y;
							*newLine >> lastObject->Scale.z;
						}
						else if (lineElement == L"*TM_SCALEAXIS") // Transform scale axis..
						{
							*newLine >> lastObject->ScaleAxis.x;
							*newLine >> lastObject->ScaleAxis.y;
							*newLine >> lastObject->ScaleAxis.z;
						}
						else if (lineElement == L"*TM_SCALEAXISANG") // Transform scale axis angle.
						{
							*newLine >> lastObject->ScaleAxisAngle;
						}
					} while (lineElement != L"}");
					lineElement = L"";
				}
				else if (lineElement == L"*SHAPE_LINE") // Shape Lline data.
				{
					// Insert new shape line into the last shape object lines.
					lastObject->lines.push_back(ShapeLine());
					ShapeLine* lastLine = &lastObject->lines.back();

					do // Iterate all the anidated lines in the shape line block.
					{
						// Line in shape line block.
						wStream.getline(line, 256);
						delete newLine; newLine = new wistringstream(line, wistringstream::in);

						// Get the first line element.
						*newLine >> lineElement;

						if (lineElement == L"*SHAPE_VERTEX_KNOT" || lineElement == L"*SHAPE_VERTEX_INTERP") // Vertex found.
						{
							// Insert new vertex in the last shaoe line.
							lastLine->vertices.push_back(LineVertex());
							LineVertex* lastVertex = &lastLine->vertices.back();

							lastVertex->VertexKind = lineElement == L"*SHAPE_VERTEX_KNOT" ? LineVertex::KNOT : LineVertex::INTERPOLATION;

							*newLine >> lineElement;

							*newLine >> lastVertex->Position.x;
							*newLine >> lastVertex->Position.y;
							*newLine >> lastVertex->Position.z;
						}
						

					} while (lineElement != L"}");
					lineElement = L"";
				}
			} while (lineElement != L"}");
		}

		// Delete teh stream object.
		delete newLine;
	}
}
