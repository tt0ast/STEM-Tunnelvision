/*
  ==============================================================================

    DelayLine.cpp
    Created: 17 May 2024 11:15:30am
    Author:  Till

  ==============================================================================
*/

#include "DelayLine.h"

void DelayLine::setup(int maxDelayInSamples)
{
    buffer.assign(maxDelayInSamples, 0.f);
}

void DelayLine::pushSample (float sample)
{
    buffer[writeIndex] = sample;
    writeIndex++;
    if (writeIndex >= buffer.size()) {
        writeIndex -= buffer.size();
    }
}

float DelayLine::getSample(int delayInSamples)
{
    if (delayInSamples < buffer.size())
    {
        auto offset = writeIndex - delayInSamples;

        if (offset < 0)
            offset += buffer.size();
            
        return buffer[offset];

    }

    else {
        return 0.f;
    }

}