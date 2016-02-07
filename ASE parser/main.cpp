#include "ASEparser.h"
#include <iomanip>  
using namespace ASEParser;

void ImportToLeafLibrary(wstring importFilename, wstring outFilename, double scale = 1.0f, Vector3 translation = Vector3());

int main()
{
	double scale = 1.0;
	double offsetX = 0.0;
	double offsetY = 0.0;

	while (true)
	{
		system("CLS");
		wcout << "Scale:" << scale << "  OffsetX: " << offsetX << "  OffsetY: " << offsetY << endl;
		wcout << "1) Change Scale" << endl << "2) Change OffsetX" << endl << "3) Change OffsetY" << endl;
		int selection;
		wcin >> selection;

		if (selection == 1)
		{
			wcout << "New Scale: ";
			wcin >> scale;
		}
		else if (selection == 2)
		{
			wcout << "New OffsetX: ";
			wcin >> offsetX;
		}
		else if (selection == 3)
		{
			wcout << "New OffsetY: ";
			wcin >> offsetY;
		}
		ImportToLeafLibrary(L"input.ASE", L"output.js", scale, Vector3(offsetX, offsetY, 0));
	}
	
	return 0;
}


void ImportToLeafLibrary(wstring importFilename, wstring outFilename, double scale, Vector3 translation)
{
	wofstream outStream;
	outStream.open(outFilename);

	outStream << L"var statesData = {\"type\":\"FeatureCollection\", \"features\":[" << endl;

	Parser parser(importFilename);
	parser.Scale(scale);
	parser.Translate(translation.x, translation.y, translation.z);

	int objectIndex = 0;
	for (vector<ShapeObject>::iterator so = parser.m_shapeObjects.begin(); so != parser.m_shapeObjects.end(); so++)
	{
		bool multipoligon = so->lines.size() > 1;
		if (multipoligon)
			outStream << L"{\"type\":\"Feature\", \"id\":\"" << objectIndex + 1 << L"\", \"properties\":{\"name\":\"" << so->Name << L"\", \"density\":1000}, \"geometry\":{\"type\":\"MultiPolygon\", \"coordinates\":[";
		else
			outStream << L"{\"type\":\"Feature\", \"id\":\"" << objectIndex + 1 << L"\", \"properties\":{\"name\":\"" << so->Name << L"\", \"density\":1000}, \"geometry\":{\"type\":\"Polygon\", \"coordinates\":";

		int lineIndex = 0;
		for (vector<ShapeLine>::iterator sl = so->lines.begin(); sl != so->lines.end(); sl++)
		{
			outStream << L"[[";
			int vertexIndex = 0;
			for (vector<LineVertex>::iterator vl = sl->vertices.begin(); vl != sl->vertices.end(); vl++)
			{
				outStream << L"[";
				outStream << std::setprecision(20) << std::fixed << vl->Position.x << ", " << vl->Position.y << L"]";
				vertexIndex++;
				if(vertexIndex != sl->vertices.size())
					outStream << L", ";
			}
			outStream << L"]]";
			lineIndex++;
			if(lineIndex != so->lines.size())
				outStream << L", ";
		}

		if (multipoligon)
			outStream << L"]}}";
		else
			outStream << L"}}";

		if(objectIndex != parser.m_shapeObjects.size() - 1)
			outStream << L"," << endl;
		else
			outStream << endl;

		objectIndex++;
	}
	
	outStream << L"]};" << endl;

	outStream.close();
}