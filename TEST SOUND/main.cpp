#include <iostream>
#include <irrKlang.h>
			
using namespace irrklang;

int main(int argc, const char** argv)
{
  // start irrKlang with default parameters
  ISoundEngine* engine = createIrrKlangDevice();
  ISoundSource* music = engine->addSoundSourceFromFile("sound/sound1.ogg"); 
  ISoundSource* caisse = engine->addSoundSourceFromFile("sound/boxSound.ogg");
  ISoundSource* pas = engine->addSoundSourceFromFile("sound/Pas.ogg"); 
  if (!engine)
    return 0; // error starting up the engine
 
  // play some sound stream, looped
  music->setDefaultVolume(0.3f);
  engine->play2D(music, true);

  char i = 0;
  std::cin >> i; // wait for user to press a key

   while(i != 'q')
        {
                std::cout << "Press any key to play some sound, press 'q' to quit.\n";

                if(i=='a'){
                // play a single sound
                engine->play2D(pas,false);
                }

                if(i=='b'){
                engine->play2D(caisse,false);
                }
                std::cin >> i; // wait for user to press some key
        }


  engine->drop(); // delete engine

  return 0;
}
