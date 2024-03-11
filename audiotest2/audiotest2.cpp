// audiotest2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_common.h>
int main()
{
    int* currentlyaloc = new int(0);
    int* maxalloc = new int(0);
    std::cout << "Hello Worlad!\n";
    FMOD_Memory_GetStats(currentlyaloc, maxalloc, false);//no es 0 
    std::cout << "uso de memoria " << currentlyaloc;
    //para configurar fmod se explica cjhchi aqui 
  // https://es.stackoverflow.com/questions/607506/como-usar-fmod-en-c-con-visual-studio
   //importante no olvidar poner el lin en el input del vinculador
    FMOD::System* system;
    FMOD::Channel* channel = 0; // new FMOD::Channel(); todos os constructores son privados
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result,FMOD_ErrorString(result));

    }
    result = system->init(512, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

    }
    FMOD::Sound* s;

    //result = system->createSound("soniditos/olas2.wav",FMOD_DEFAULT,0,&s);
    //Es necesario cargar los sonidos como 3d 
    result = system->createSound("soniditos/olas2.wav",FMOD_3D,0,&s);
  //  FMOD_ADVANCEDSETTINGS* settings;
//    system->getAdvancedSettings(settings);
    

    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
    //result = system->playSound(s, 0, false, &channel);
    s->setMode(FMOD_LOOP_BIDI);
    result = system->playSound(s, 0, false, &channel);
    char i; 
    std::cin >> i;
    FMOD_VECTOR pos =   FMOD_VECTOR();
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    FMOD_VECTOR vel =  FMOD_VECTOR();
    //importante que estos  2 no esten en 0 0 0 
    FMOD_VECTOR forward =  FMOD_VECTOR();
    forward.z = 1;
    FMOD_VECTOR up =  FMOD_VECTOR();
    up.y = 1;
    
    //FMOD_VECTOR* fmodleak = new FMOD_VECTOR(); esto si deja leaks

    while (i != 'q')
    {
        std::cin >> i;

        if (i == 'a')
        {
            pos.x= pos.x +1;
            //std::cout << pos.x;
           // system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
        }
        if (i == 'd')
        {
            pos.x = pos.x - 1;
        }
        if (i == 'w')
        {
            pos.z = pos.z + 1;
        }
        if (i == 's')
        {
            pos.z = pos.z - 1;
        }
        system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
    
       result= system->update();

    }
    result = FMOD::Debug_Initialize(FMOD_DEBUG_TYPE_MEMORY);
    //printf("FMOD memory! (%d) %s\n", result);
    //se supone que hay qeu hacer esto pero si no lo haces no salen leaks?
    // que entonces se supone qeu no hay? https://forums.codeguru.com/showthread.php?531349-Show-memory-leaks-in-dll
    s->release();
    system->close();
    system->release();
    result = FMOD_Memory_GetStats(currentlyaloc, maxalloc, false);
    delete currentlyaloc;
    delete maxalloc;
    
   
    std::cout << "uso de memoria " << currentlyaloc;
    //printf("FMOD error! (%d) %s\n",result,FMOD_Memory_GetStats(0,0,false));
 
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
