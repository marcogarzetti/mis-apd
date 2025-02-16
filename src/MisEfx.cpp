//-------------------------------------------------------------------------------------------------------
//  MisEfx.cpp
//
//  Created by Marco Bertola on 02/06/2020.
//
//-------------------------------------------------------------------------------------------------------

#include "MisEfx.h"


//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance(audioMasterCallback audioMaster) //CreateEffectInstance è una funzione che utilizza l’host quando inizializza il plugin, e ritorna un puntatore al nostro plugin
{
    return new MisEfx(audioMaster);
}

//-------------------------------------------------------------------------------------------------------
MisEfx::MisEfx(audioMasterCallback audioMaster) //nel costruttore del plugin estendo la classe master passandogli dei parametri utili per la creazione del plugin)
    : AudioEffectX(audioMaster, 0, 0)	// n program, n parameters
{
    //valorizzo questi parametri per l'host
    setNumInputs(2);		// stereo in -- quanti ingressi supporto
    setNumOutputs(2);		// stereo out -- quante uscite supporto
    setUniqueID('vMis');	// identify -- imposto l'id del plugin

}

//-----------------------------------------------------------------------------------------
void MisEfx::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames)
{
    // PROCESS SINGLE PRECISION

    float* inL = inputs[0]; // buffer input left
    float* inR = inputs[1]; // buffer input right

    float* outL = outputs[0]; // buffer output left
    float* outR = outputs[1]; // buffer output right

}

int MisEfx::getSamplerate() { //esempio metodo definito in MisEfx.h, qui viene implementato e ritorna sampleRate, una variabile ereditata dalla classe AudioEffect
    return sampleRate;
}
//-------------------------------------------------------------------------------------------------------
MisEfx::~MisEfx()
{

}


