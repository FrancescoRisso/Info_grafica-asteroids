#include "displayString.hpp"

using namespace Asteroids;

DisplayString::DisplayString() {}

void DisplayString::Draw() const {
	for(int i = 0; i < letterObjects.size(); i++) letterObjects[i].Draw();
}


void DisplayString::updateTransform() {
	for(int i = 0; i < letterObjects.size(); i++) letterObjects[i].updateTransform();
}


void DisplayString::Init(glm::vec2 pos, const char* s, horizAligns horizontalAlignment, vertAligns verticalAlignment, glm::vec3 color, float height) {
	this->horizontalAlignment = horizontalAlignment;
	this->verticalAlignment = verticalAlignment;
	this->color = color;
	this->height = height;

	int i = 0;
	while(s[i] != '\0') {
		Letter l;
		l.Init(pos, s[i], horizontalAlignment, verticalAlignment, color, height);

		charSequence.push_back(s[i]);
		letterObjects.push_back(l);
		++i;
	}

	shiftLetters();
}


void DisplayString::shiftLetters() {
	int totSize;

	switch(horizontalAlignment) {
		case alignLeft:
			totSize = -1;
			for(int i = 0; i < letterObjects.size(); i++) {
				letterObjects[i].shiftByPixel(++totSize);
				totSize += letterObjects[i].getWidth();
			}
			break;

		case alignRight:
			totSize = 1;
			for(int i = letterObjects.size() - 1; i >= 0; i--) {
				totSize -= letterObjects[i].getWidth();
				letterObjects[i].shiftByPixel(--totSize);
			}
			break;

		case alignCenterHoriz:
			totSize = -1;
			float mid;

			for(int i = 0; i < letterObjects.size(); i++) totSize += 1 + letterObjects[i].getWidth();
			mid = (float) totSize / 2;
			totSize = 0;

			for(int i = 0; i < letterObjects.size(); i++) {
				letterObjects[i].shiftByPixel(++totSize - mid);
				totSize += letterObjects[i].getWidth();
			}
			break;
	}
}
