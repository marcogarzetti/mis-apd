//-------------------------------------------------------------------------------------------------------
//  MisEfx.cpp
//
//  Created by Marco Bertola on 02/06/2020.
//
//-------------------------------------------------------------------------------------------------------

#include "MisEfx.h"
//#include "MisEfxUtils.h"
#define PARAM_GAIN_MIN = 0.0
#define PARAM_GAIN_MAX = 3.0


//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance(audioMasterCallback audioMaster) //CreateEffectInstance è una funzione che utilizza l’host quando inizializza il plugin, e ritorna un puntatore al nostro plugin
{
	return new MisEfx(audioMaster);
}

//-------------------------------------------------------------------------------------------------------
MisEfx::MisEfx(audioMasterCallback audioMaster) //nel costruttore del plugin estendo la classe master passandogli dei parametri utili per la creazione del plugin)
	: AudioEffectX(audioMaster, 0, 2)	// n program, n parameters
{
	//valorizzo questi parametri per l'host
	setNumInputs(2);		// stereo in -- quanti ingressi supporto
	setNumOutputs(2);		// stereo out -- quante uscite supporto
	setUniqueID('vMis');	// identify -- imposto l'id del plugin

	//definisco parametri necessari al plugin (imposto anche il numero di parametri supportati quando chiamo il costruttore di AudioEffectX
	MisEfx::gain = 1; //da 0 a 1
	MisEfx::bypass = 0;
	MisEfx::pan = 0.5;
}

//-----------------------------------------------------------------------------------------
void MisEfx::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames)
{
	// PROCESS SINGLE PRECISION

	float* inL = inputs[0]; // buffer input left
	float* inR = inputs[1]; // buffer input right

	float* outL = outputs[0]; // buffer output left
	float* outR = outputs[1]; // buffer output right

	if (bypass < 0.5)
	{
		for (int i = 0; i < sampleFrames; i++)
		{
			outL[i] = inL[i] * gain;
			outR[i] = inR[i] * gain;
		}
	}
	if (bypass > 0.5)
	{
		for (int i = 0; i < sampleFrames; i++)
		{
			outL[i] = inL[i];
			outR[i] = inR[i];
		}
	}
}

//parameters methods implementation
void MisEfx::setParameter(VstInt32 index, float value)	///< Called when a parameter changed
{
	switch (index)
	{
	case Params_gain: gain = value;break;
	case Params_bypass: bypass = value;break;
	
	}
}

float MisEfx::getParameter(VstInt32 index)	///< Return the value of the parameter with \e index
{
	float ret = 0;
	switch (index)
	{
	case Params_gain: ret = gain;break;
	case Params_bypass: ret = bypass;break;
	}
	return ret;
}

void MisEfx::getParameterLabel(VstInt32 index, char* label) ///< Stuff \e label with the units in which parameter \e index is displayed (i.e. "sec", "dB", "type", etc...). Limited to #kVstMaxParamStrLen.
{
	switch (index)
	{
	case Params_gain: vst_strncpy(label, "dB", kVstMaxParamStrLen);break;
	case Params_bypass: vst_strncpy(label, "on/off", kVstMaxParamStrLen);break;
	}

	//i could do like this, but is not safe because if the string exceeds the buffer lenght the application will crash
	//label = "Gain";
}
void MisEfx::getParameterDisplay(VstInt32 index, char* text) ///< Stuff \e text with a string representation ("0.5", "-3", "PLATE", etc...) of the value of parameter \e index. Limited to #kVstMaxParamStrLen.
{

	switch (index)
	{
	case Params_gain: float2string(gain, text, kVstMaxParamStrLen);break;
	case Params_bypass: (bypass < 0.5) 
		? vst_strncpy(text, "Off", kVstMaxParamStrLen) 
		: vst_strncpy(text, "On", kVstMaxParamStrLen);break;
	}
	//float2string converts to a string the value of the float variable gain

}
void MisEfx::getParameterName(VstInt32 index, char* text) ///< Stuff \e text with the name ("Time", "Gain", "RoomType", etc...) of parameter \e index. Limited to #kVstMaxParamStrLen.
{
	switch (index)
	{
	case Params_gain: vst_strncpy(text, "Gain", kVstMaxParamStrLen);break;
	case Params_bypass: vst_strncpy(text, "Bypass", kVstMaxParamStrLen);;break;
	}
}

int MisEfx::getSamplerate() { //esempio metodo definito in MisEfx.h, qui viene implementato e ritorna sampleRate, una variabile ereditata dalla classe AudioEffect
	return sampleRate;
}
//-------------------------------------------------------------------------------------------------------
MisEfx::~MisEfx()
{

}


