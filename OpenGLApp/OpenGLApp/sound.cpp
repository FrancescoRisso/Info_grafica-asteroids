#include "sound.hpp"
using namespace irrklang;

static ISoundEngine* engine = createIrrKlangDevice();

 irrklang::ISound* snd;

void soundOn() {

	snd=engine->play2D("./resources/sounds/beatwave.mp3", true);
	GactiveChange();
	HactiveChange();
	//if(snd) {
	//	snd->setPlaybackSpeed(0.1f);
	//	snd->drop();
	//	snd = 0;
	//}
}

void soundOff() {
	engine->play2D("off", false);
	GactiveChange();
	HactiveChange();
}

int soundPrepare() {
	// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();

	if(!engine) return 0;  // error starting up the engine

	// play some sound stream, looped
	

	//char i = 0;
	//std::cin >> i;  // wait for user to press some key

	engine->drop();  // delete engine
	return 0;
}