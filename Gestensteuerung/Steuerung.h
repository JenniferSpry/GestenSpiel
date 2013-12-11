#ifndef STEUERUNG_H
#define STEUERUNG_H

class Steuerung{
public:
	Steuerung();
	~Steuerung();
	void initialize(float sampleRate);
	float processOneSample(float);
	void process(float* input, float*output, int numberOfSamples);
	void setGain(float gain);
private:
	float sampleRate;
	float gain;
};
#endif