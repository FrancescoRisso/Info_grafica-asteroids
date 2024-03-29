#include "displayString.hpp"

using namespace Asteroids;

DisplayString::DisplayString() {}

void DisplayString::Draw() const {
	for(int i = 0; i < letterObjects.size(); i++) letterObjects[i].Draw();
}


void DisplayString::updateTransform() {
	pos = scaleVector(unscaledPos);
	for(int i = 0; i < letterObjects.size(); i++) {
		letterObjects[i].updatePos(pos);
		letterObjects[i].updateTransform();
	}
}


void DisplayString::Init(glm::vec2 pos, const char* s, horizAligns horizontalAlignment, vertAligns verticalAlignment, glm::vec3 color, float height) {
	this->horizontalAlignment = horizontalAlignment;
	this->verticalAlignment = verticalAlignment;
	this->color = color;
	this->height = height;
	this->unscaledPos = pos;
	this->pos = scaleVector(unscaledPos);

	charSequence.clear();
	letterObjects.clear();

	int i = 0;
	while(s[i] != '\0') {
		Letter l;
		l.Init(this->pos, s[i], horizontalAlignment, verticalAlignment, color, height);

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
				letterObjects[i].shiftByPixel((float) ++totSize);
				totSize += letterObjects[i].getWidth();
			}
			break;

		case alignRight:
			totSize = 1;
			for(int i = (int) letterObjects.size() - 1; i >= 0; i--) {
				totSize -= letterObjects[i].getWidth();
				letterObjects[i].shiftByPixel((float) --totSize);
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


void DisplayString::changeString(const char* newString) {
	Init(unscaledPos, newString, horizontalAlignment, verticalAlignment, color, height);
}


void DisplayString::setColor(glm::vec3 newColor) {
	color = newColor;
	for(int i = 0; i < letterObjects.size(); i++) letterObjects[i].setColor(newColor);
}
