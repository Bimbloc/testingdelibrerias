// audiotest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
// 

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <irrKlang.h>
#include <string>
#include <fmod.hpp>

using namespace irrklang;
using namespace std;
int main()
{
    std::cout << "Hello World!\n";
    //para configurar fmod se explica cjhchi aqui 
   // https://es.stackoverflow.com/questions/607506/como-usar-fmod-en-c-con-visual-studio
    //importante no olvidar poner el lin en el input del vinculador
   // FMOD::System* system;
    //FMOD_RESULT result = FMOD::System_Create(&system);


    //esto es un slay irrKlang manages the memory usage of sounds by itself
   // https://www.ambiera.com/irrklang/docu/index.html#sound3d
    ISoundEngine* engine = createIrrKlangDevice();
    //int* leak = new int(3);
   // std::string* a = new std::string("aaa");
   if (!engine)
        return 0; // error starting up the engine
   int x = 0;
   int y = 0;
   int z = 0;
    vec3df position(x, y, z);
    //soporta wav exportados en unsigned 8 bit pcm
    irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
    irrklang::vec3df velPerSecond(0, 0, 0);    // only relevant for doppler effects ojoooo que te calcula el doppler
    irrklang::vec3df upVector(0, 1, 0);
    //audio en 3d se esàcializa guay!
    ISound* snd = engine->play3D("soniditos/olas2.wav", position, true,true);//tienes que crearlo pausado si luego quieres acceder al el 
    snd->setIsPaused(false);
    // play some sound stream, looped en 2d
    //engine->play2D("soniditos/snare1.wav", true);
    string a;
    char i = 0;
    while (i != 'q')
    {
        std::cin >> i; // wait for user to press some key
        std::getline(cin, a);
        if (a == "b")
        {
            cout << "aaa";
        }
        if (i == 'w')
        {
            z++;
        }
        if (i == 's')
        {
            z--;
        }
        if (i == 'a')
        {
            x--;

        }
        if (i == 'd')
        {
            x++;
        }
        //podemos mover el sonido
       // position = vec3df(x, y, z);
       // snd->setPosition(position);
       
        //o podemos mover al listener
        position = vec3df (x,y, z);        // position of the listener
             // where 'up' is in your 3D scene
       
        engine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
    }
    engine->drop(); // delete engine par aque no deje leaks
   // system->release();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    //return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
