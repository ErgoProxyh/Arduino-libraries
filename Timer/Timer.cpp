/**
 *
    This file is part of .PNG Arduino Framework.

    .PNG Arduino Framework is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    .PNG Arduino Framework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with .PNG Arduino Framework.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "Timer.h"

Timer::Timer(unsigned long int ms){
	Create(ms, NULL, false, millis);
}

Timer::Timer(unsigned long int ms, CallBackType callback, MillisType mst){
	Create(ms, callback, false, mst);
}

Timer::Timer(unsigned long int ms, CallBackType callback, bool isSingle){
	Create(ms, callback, isSingle, millis);
}

void Timer::Create(unsigned long int ms, CallBackType callback, bool isSingle, MillisType mst){
	setInterval(ms);
	setEnabled(false);
	setSingleShot(isSingle);
	setOnTimer(callback);
	LastTime = 0;
    millis2 = mst;
}

void Timer::setInterval(unsigned long int ms){
	msInterval = (ms > 0) ? ms : 0;
}

void Timer::setEnabled(bool Enabled){
	blEnabled = Enabled;
}

void Timer::setSingleShot(bool isSingle){
	blSingleShot = isSingle;
}

void Timer::setOnTimer(CallBackType callback){
	onRun = callback;
}

void Timer::Start(){
	LastTime = millis2();
	setEnabled(true);
}

void Timer::Resume(){
	LastTime = millis2() - DiffTime;
	setEnabled(true);
}

void Timer::Stop(){
	setEnabled(false);

}

void Timer::Pause(){
	DiffTime = millis2() - LastTime;
	setEnabled(false);

}

void Timer::Update(){
	if(Tick())
		onRun();
}

bool Timer::Tick(){
	if(!blEnabled)
		return false;
	if(LastTime > millis2()*2)//millis restarted
		LastTime = 0;
	if ((unsigned long int)(millis2() - LastTime) >= msInterval) {
		LastTime = millis2();
		if(isSingleShot())
			setEnabled(false);
	    return true;
	}
	return false;
}


unsigned long int Timer::getInterval(){
	return msInterval;
}

unsigned long int Timer::getCurrentTime(){
	return (unsigned long int)(millis2() - LastTime);
}
CallBackType Timer::getOnTimerCallback(){
	return onRun;
}

bool Timer::isEnabled(){
	return blEnabled;
}

bool Timer::isSingleShot(){
	return blSingleShot;
}
