#include "SaveFile.h"
#include <algorithm>
#include <iostream>
#include <string>


SaveFile::SaveFile()
{
	auto res = doc.load_file("resources/save.xml");
	if (!res)
	{
		std::cerr << "Could not open file visage.xml because " << res.description() << std::endl;
		return;
	}

	pugi::xml_node node = doc.child("Save");

	for (pugi::xml_node line : node.children()) {

		bestAlt.push_back(line.attribute("score").as_float());

	}
	
	std::sort(bestAlt.begin(), bestAlt.end(),std::greater<>());

}

void SaveFile::addScore(float alt)
{

	for (int i = 0; i < 10; i++) {

		if (bestAlt[i] < alt) {
			for (int j = 9; j > i; j--) {
				bestAlt[j] = bestAlt[j - 1];
			}
			bestAlt[i] = alt;
			break;
		}

	}

}

void SaveFile::printScores()
{

	for (auto score : bestAlt) {
		printf("Hauteur : %f\n", score);
	}

}

void SaveFile::saveToDisk() const
{
	int i = 0;

	for (pugi::xml_node line : doc.child("Save")) {
		
		line.attribute("score").set_value(std::to_string(bestAlt[i]).c_str());
		i++;
	}
	
	doc.save_file("resources/save.xml","\t");
}

std::vector<float> SaveFile::getScores() const
{
	return bestAlt;
}


