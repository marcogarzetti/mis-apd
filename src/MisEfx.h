//-------------------------------------------------------------------------------------------------------
//  MisEfx.h
//
//  Created by Marco Bertola on 02/06/2020.
//
//-------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "public.sdk/source/vst2.x/audioeffectx.h"

using namespace std;

enum Params
{
	Params_gain,
	Params_bypass,
	Params_pan
};

//-------------------------------------------------------------------------------------------------------
class MisEfx : public AudioEffectX
{


public:

	MisEfx(audioMasterCallback audioMaster);
	~MisEfx();

	float gain;
	float bypass;
	float pan;

	// Processing
	virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override;

	//parameter methods definition
	void setParameter(VstInt32 index, float value) override;	///< Called when a parameter changed
	float getParameter(VstInt32 index) override;	///< Return the value of the parameter with \e index
	void getParameterLabel(VstInt32 index, char* label) override;	///< Stuff \e label with the units in which parameter \e index is displayed (i.e. "sec", "dB", "type", etc...). Limited to #kVstMaxParamStrLen.
	void getParameterDisplay(VstInt32 index, char* text) override;	///< Stuff \e text with a string representation ("0.5", "-3", "PLATE", etc...) of the value of parameter \e index. Limited to #kVstMaxParamStrLen.
	void getParameterName(VstInt32 index, char* text) override;    ///< Stuff \e text with the name ("Time", "Gain", "RoomType", etc...) of parameter \e index. Limited to #kVstMaxParamStrLen.


	int getSamplerate();

};


