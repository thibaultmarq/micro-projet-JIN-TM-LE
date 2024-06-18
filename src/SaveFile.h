#pragma once
#include <vector>
#include "pugixml.hpp"


class SaveFile {

private:

	std::vector<float> bestAlt;
	pugi::xml_document doc;

public:

	explicit SaveFile();
	void addScore(float alt);
	void printScores();


	void saveToDisk() const;

	std::vector<float> getScores() const;



};