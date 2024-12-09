/*
  ==============================================================================

    delayLine.h
    Created: 17 May 2024 11:15:30am
    Author:  Till

  ==============================================================================
*/
#include <vector>

class DelayLine
{
public:
    DelayLine() = default;

    void setup (int maxDelaySamples);

    void pushSample (float sample);

    float getSample (int delayInSamples);

private:
    std::vector<float> buffer;
    int writeIndex{ 0 };
};

