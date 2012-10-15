/********************************************************************************************************************** 
* THE OMICRON PROJECT
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright 2010								Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Arthur Nishimoto							anishimoto42@gmail.com
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright (c) 2010, Electronic Visualization Laboratory, University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
 * following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
 * and the following disclaimer in the documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************************************/

#include "omicron/Sound.h"

using namespace omicron;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nextBufferID = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Sound(const String& soundName)
{
	this->soundName = soundName;
	bufferID = nextBufferID;
	nextBufferID++;
	
	volumeScale = 1.0f;
	volume = 0.5f;
	width = 1.0f;
	mix = 0.0f;
	reverb = 0.0f;
	loop = false;

	minRolloffDistance = 1.0f;
	maxDistance = 500.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Sound(const String& soundName, float volume, float width, float mix, float reverb, bool loop, bool env)
{
	this->soundName = soundName;
	bufferID = nextBufferID;
	nextBufferID++;
	
	volumeScale = 1.0f;
	this->volume = volume;
	this->width = width;
	this->mix = mix;
	this->reverb = reverb;
	this->loop = loop;
	this->environmentSound = env;

	minRolloffDistance = 1.0f;
	maxDistance = 500.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setDefaultParameters(float volume, float width, float mix, float reverb, bool loop, bool env)
{
	this->volume = volume;
	this->width = width;
	this->mix = mix;
	this->reverb = reverb;
	this->loop = loop;
	this->environmentSound = env;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::loadFromFile(const String& filePath)
{
	this->filePath = filePath;

	Message msg("/loadBuffer");
	msg.pushInt32(this->getBufferID());
	msg.pushStr(this->getFilePath());
	environment->getSoundManager()->sendOSCMessage(msg);
	ofmsg("Loaded buffer ID %1% with path %2%", %this->getBufferID() %this->getFilePath());
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::loadFromMemory(const void* buf, size_t length)
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDuration()
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setVolumeScale(float volume)
{
	volumeScale = volume;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getVolumeScale()
{
	return volumeScale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultVolume()
{
	return volume;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultMix()
{
	return mix;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultReverb()
{
	return mix;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultWidth()
{
	return width;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isDefaultLooping()
{
	return loop;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isEnvironmentSound()
{
	return environmentSound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setSoundEnvironment(SoundEnvironment* env)
{
	this->environment = env;
	environment->addBufferID( bufferID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundEnvironment* Sound::getSoundEnvironment()
{
	return environment;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sound::getBufferID()
{
	return bufferID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String& Sound::getFilePath()
{
	return filePath;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nextInstanceID = 4001;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundInstance::SoundInstance(Sound* sound)
{
	this->sound = sound;
	instanceID = nextInstanceID; // This should be globally incremented on each new instance. Must be 1001 or greater.
	nextInstanceID++;
	
	volume = sound->getDefaultVolume();
	width = sound->getDefaultWidth();
	mix = sound->getDefaultMix();
	reverb = sound->getDefaultReverb();
	loop = sound->isDefaultLooping();
	environmentSound = sound->isEnvironmentSound();

	environment = sound->getSoundEnvironment();
	environment->addInstanceID(instanceID);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundInstance::~SoundInstance()
{
	//stop();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setLoop(bool value)
{
	loop = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::play()
{
	//printf( "%s: Playing buffer %d with instanceID: %d\n", __FUNCTION__, sound->getBufferID(), instanceID);
	Message msg("/play");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	if( volume * sound->getVolumeScale() > 1 )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( volume * sound->getVolumeScale() );

	msg.pushFloat( position[0] );
	msg.pushFloat( position[1] );
	msg.pushFloat( position[2] );
	
	Vector3f audioListener = environment->getListenerPosition();
	msg.pushFloat( audioListener[0] );
	msg.pushFloat( audioListener[1] );
	msg.pushFloat( audioListener[2] );

	// Width - nSpeakers 1-20
	if( environmentSound )
		msg.pushFloat( 20 );
	else
		msg.pushFloat( width );

	// Mix - wetness of sound 0.0 - 1.0
	msg.pushFloat( mix );

	// Room size - reverb amount 0.0 - 1.0
	msg.pushFloat( reverb );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playStereo()
{
	//printf( "%s: Playing buffer %d with instanceID: %d\n", __FUNCTION__, sound->getBufferID(), instanceID);
	Message msg("/playStereo");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	if( volume * sound->getVolumeScale() > 1 )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( volume * sound->getVolumeScale() );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::getLoop()
{
	return loop;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::play( Vector3f position, float volume, float width, float mix, float reverb, bool loop )
{
	//printf( "%s: Playing buffer %d with instanceID: %d\n", __FUNCTION__, sound->getBufferID(), instanceID);
	Message msg("/play");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	if( volume * sound->getVolumeScale() > 1 )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( volume * sound->getVolumeScale() );

	msg.pushFloat( position[0] );
	msg.pushFloat( position[1] );
	msg.pushFloat( position[2] );
	
	Vector3f audioListener = environment->getListenerPosition();
	msg.pushFloat( audioListener[0] );
	msg.pushFloat( audioListener[1] );
	msg.pushFloat( audioListener[2] );

	// Width - nSpeakers 1-20
	msg.pushFloat( width );

	// Mix - wetness of sound 0.0 - 1.0
	msg.pushFloat( mix );

	// Room size - reverb amount 0.0 - 1.0
	msg.pushFloat( reverb );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playStereo( float volume, bool loop )
{
	//printf( "%s: Playing buffer %d with instanceID: %d\n", __FUNCTION__, sound->getBufferID(), instanceID);
	Message msg("/playStereo");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	if( volume * sound->getVolumeScale() > 1 )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( volume * sound->getVolumeScale() );
	
	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::pause()
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::stop()
{
	//printf( "%s: Freeing instanceID: %d\n", __FUNCTION__, instanceID);
	Message msg("/freeNode");
	msg.pushInt32(instanceID);
	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isPlaying()
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setPosition(Vector3f pos)
{
	position = pos;

	Message msg("/setObjectLoc");
	msg.pushInt32(instanceID);

	msg.pushFloat( position[0] );
	msg.pushFloat( position[1] );
	msg.pushFloat( position[2] );

	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3f& SoundInstance::getPosition()
{
	return position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isEnvironmentSound()
{
	return environmentSound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setEnvironmentSound(bool value)
{
	environmentSound = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setVolume(float value)
{
	this->volume = value;

	printf( "%s: for instanceID: %d\n", __FUNCTION__, instanceID);
	Message msg("/setVol");
	msg.pushInt32(instanceID);
	msg.pushFloat(this->volume);
	environment->getSoundManager()->sendOSCMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getVolume()
{
	return volume;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setWidth(float value)
{
	this->width = value;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getWidth()
{
	return width;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setMix(float value)
{
	this->volume = value;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getMix()
{
	return mix;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setReverb(float value)
{
	this->reverb = value;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getReverb()
{
	return reverb;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setMaxDistance(float value)
{
	this->maxDistance = value;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getMaxDistance()
{
	return maxDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setMinRolloffDistance(float value)
{
	this->minRolloffDistance = value;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getMinRolloffDistance()
{
	return minRolloffDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setDistanceRange(float min, float max)
{
	this->minRolloffDistance = min;
	this->maxDistance = max;
	printf( "%s: Not fully implemented yet \n", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setSoundEnvironment(SoundEnvironment* environment)
{
	this->environment = environment;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundInstance::getID()
{
	return instanceID;
}
