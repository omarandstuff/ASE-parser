#include "ASEparser.h"
using namespace ASEParser;

int main()
{
	wstring filename = L"test.ASE";

	wcout << "Parising " << filename << endl;

	Parser parser(L"test.ASE");

	parser.Scale(0.001);
	parser.Translate(-5, -10, 20);

	wcout << "Shape objects count: " << parser.m_shapeObjects.size() << endl << endl;
	for (vector<ShapeObject>::iterator it = parser.m_shapeObjects.begin(); it != parser.m_shapeObjects.end(); it++)
	{
		wcout << "Shape: " << it->Name << endl;
		wcout << "Line count: " << it->lines.size() << endl << endl;

		for (vector<ShapeLine>::iterator sl = it->lines.begin(); sl != it->lines.end(); sl++)
		{
			static int lineIndex = 0;
			wcout << "Line_" << lineIndex << endl;
			wcout << "Vertex count: " << sl->vertices.size() << endl << endl;

			for (vector<LineVertex>::iterator lv = sl->vertices.begin(); lv != sl->vertices.end(); lv++)
			{
				wcout << (lv->VertexKind == LineVertex::KNOT ? "VERTEX KNOT: " : "VERTEX INTERPOLATED: ") << lv->Position.x << ", " << lv->Position.y << ", " << lv->Position.z << endl;
			}

			wcout << endl;
			lineIndex++;
		}
	}

	wcin >> filename;

	return 0;
}
