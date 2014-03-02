/*
 * Animation.cpp
 *
 *  Created on: 2014-3-2
 *      Author: Hali
 */

#include "Animation.h"
#include <algorithm>

const string Animation::NONE = "none";
const string Animation::SAME_LAYER = "sameLayer";
const string Animation::SAME_GROUP = "sameGroup";
const string Animation::SAME_LAYER_AND_GROUP = "sameLayerAndGroup";
const string Animation::ALL = "all";

Animation::Animation(Armature* armature) :
		_armature(NULL), _isActive(false), tweenEnabled(true), _lastAnimationState(NULL) {
	// TODO Auto-generated constructor stub
	_isPlaying = false;
	_timeScale = 1;

	_armature = armature;
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

/**
 * An vector containing all AnimationData names the Animation can play.
 * @see dragonBones.objects.AnimationData.
 */
vector<string> & Animation::getMovementList() {
	return _animationList;
}

string Animation::getMovementID() {
	return _lastAnimationState ? _lastAnimationState->getName() : string("");
}

AnimationState* Animation::getLastAnimationState() {
	return _lastAnimationState;
}

vector<string> & Animation::getAnimationList() {
	return _animationList;
}

bool Animation::getIsPlaying() {
	return _isPlaying && _isActive;
}

bool Animation::getIsComplete() {
	if (_lastAnimationState) {
		if (!_lastAnimationState->getIsComplete()) {
			return false;
		}
		unsigned int j = _animationLayer.size();
		while (j--) {
			vector<AnimationState*> & animationStateList = _animationLayer[j];
			unsigned int i = animationStateList.size();
			while (i--) {
				if (!animationStateList[i]->getIsComplete()) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

vector<AnimationData*> & Animation::getAnimationDataList() {
	return _animationDataList;
}

void Animation::setAnimationDataList(vector<AnimationData*> & value) {
	_animationDataList = value;
	_animationList.clear();
	for (unsigned int i = 0; i < _animationDataList.size(); i++) {
		AnimationData* animationData = _animationDataList[i];
		_animationList.push_back(animationData->getName());
	}
}

float Animation::getTimeScale() {
	return _timeScale;
}

void Animation::setTimeScale(float value) {
	if (value < 0) {
		value = 0;
	}
	_timeScale = value;
}

void Animation::dispose() {
	if (!_armature) {
		return;
	}
	stop();
	unsigned int i = _animationLayer.size();
	while (i--) {
		vector<AnimationState*> & animationStateList = _animationLayer[i];
		unsigned int j = animationStateList.size();
		while (j--) {
			AnimationState::returnObject(animationStateList[j]);
		}
		animationStateList.clear();
	}
	_animationLayer.clear();
	_animationList.clear();

	_armature = NULL;
}

AnimationState* Animation::gotoAndPlay(string animationName, float fadeInTime/* = -1*/, float duration/* = -1*/,
		float loop/* = -1*/, unsigned int layer/* = 0*/, string group/* = string("")*/,
		string fadeOutMode/* = SAME_LAYER_AND_GROUP*/, bool displayControl/* = true*/, bool pauseFadeOut/* = true*/,
		bool pauseFadeIn/* = true*/
		) {
	if (!_animationDataList) {
		return NULL;
	}
	unsigned int i = _animationDataList.size();
	AnimationData* animationData = NULL;
	while (i--) {
		if (_animationDataList[i]->getName() == animationName) {
			animationData = _animationDataList[i];
			break;
		}
	}
	if (!animationData) {
		return NULL;
	}

	_isPlaying = true;

	float dataFadeInTime = animationData->getFadeInTime();
	dataFadeInTime = dataFadeInTime < 0 ? 0.3f : dataFadeInTime;
	fadeInTime = fadeInTime < 0 ? dataFadeInTime : fadeInTime;

	float dataScale = animationData->getScale();
	float dataDuration = animationData->getDuration();
	float durationScale;
	if (duration < 0) {
		durationScale = dataScale < 0 ? 1 : dataScale;
	} else {
		durationScale = duration / dataDuration;
	}

	loop = (loop == -1 ? animationData->loop : loop);
	layer = addLayer(layer);

	//autoSync = autoSync && !pauseFadeOut && !pauseFadeIn;
	AnimationState* animationState = NULL;
	vector<AnimationState*> animationStateList;
	unsigned int j = 0;
	if (fadeOutMode == NONE) {

	} else if (fadeOutMode == SAME_LAYER) {
		animationStateList = _animationLayer[layer];
		i = animationStateList.size();
		while (i--) {
			animationState = animationStateList[i];
			animationState->fadeOut(fadeInTime, pauseFadeOut);
		}
	} else if (fadeOutMode == SAME_GROUP) {
		j = _animationLayer.size();
		while (j--) {
			animationStateList = _animationLayer[j];
			i = animationStateList.size();
			while (i--) {
				animationState = animationStateList[i];
				if (animationState->getGroup() == group) {
					animationState->fadeOut(fadeInTime, pauseFadeOut);
				}
			}
		}
	} else if (fadeOutMode == ALL) {
		j = _animationLayer.size();
		while (j--) {
			animationStateList = _animationLayer[j];
			i = animationStateList.size();
			while (i--) {
				animationState = animationStateList[i];
				animationState->fadeOut(fadeInTime, pauseFadeOut);
			}
		}
	} else if (fadeOutMode == SAME_LAYER_AND_GROUP) {
		animationStateList = _animationLayer[layer];
		i = animationStateList.size();
		while (i--) {
			animationState = animationStateList[i];
			if (animationState->getGroup() == group) {
				animationState->fadeOut(fadeInTime, pauseFadeOut);
			}
		}
	} else {
		animationStateList = _animationLayer[layer];
		i = animationStateList.size();
		while (i--) {
			animationState = animationStateList[i];
			if (animationState->getGroup() == group) {
				animationState->fadeOut(fadeInTime, pauseFadeOut);
			}
		}
	}

	_lastAnimationState = AnimationState::borrowObject();
	_lastAnimationState->setGroup(group);
	_lastAnimationState->setTweenEnabled(tweenEnabled);
	_lastAnimationState->fadeIn(_armature, animationData, fadeInTime, 1 / durationScale, loop, layer, displayControl,
			pauseFadeIn);

	addState(_lastAnimationState);

	vector<Slot*> & slotList = _armature->_slotList;
	Slot* slot = NULL;
	i = slotList.size();
	while (i--) {
		slot = slotList[i];
		Armature* childArmature = slot->getChildArmature();
		if (childArmature != NULL) {
			childArmature->getAnimation()->gotoAndPlay(animationName, fadeInTime);
		}
	}

	_lastAnimationState->advanceTime(0);

	return _lastAnimationState;
}

void Animation::play() {
	if (!_animationDataList || _animationDataList.empty()) {
		return;
	}

	if (!_lastAnimationState) {
		gotoAndPlay(_animationDataList[0]->getName());
	} else if (!_isPlaying) {
		_isPlaying = true;
	} else {
		gotoAndPlay(_lastAnimationState->getName());
	}
}

void Animation::stop() {
	_isPlaying = false;
}

AnimationState* Animation::getState(string name, unsigned int layer/* = 0*/) {
	unsigned int l = _animationLayer.size();
	if (l == 0) {
		return NULL;
	} else if (layer >= l) {
		layer = l - 1;
	}

	vector<AnimationState*> & animationStateList = _animationLayer[layer];
	if (!animationStateList) {
		return NULL;
	}

	unsigned int i = animationStateList.size();
	while (i--) {
		if (animationStateList[i]->getName() == name) {
			return animationStateList[i];
		}
	}

	return NULL;
}

bool Animation::hasAnimation(string animationName) {
	unsigned int i = _animationDataList.size();
	while (i--) {
		if (_animationDataList[i]->getName() == animationName) {
			return true;
		}
	}

	return false;
}

void Animation::advanceTime(float passedTime) {
	/*
	 if(!_isPlaying || !_isActive)
	 {
	 return;
	 }
	 */
	passedTime *= _timeScale;

	unsigned int l = _armature->_boneList.size();
	int i = 0;
	int j = 0;
	int k = l;
	unsigned int stateListLength = 0;
	Bone* bone = NULL;
	string boneName = "";
	float weigthLeft = 0;

	float x = 0;
	float y = 0;
	float skewX = 0;
	float skewY = 0;
	float scaleX = 0;
	float scaleY = 0;
	float pivotX = 0;
	float pivotY = 0;

	float layerTotalWeight = 0;
	vector<AnimationState*> animationStateList;
	AnimationState* animationState = NULL;
	TimelineState* timelineState = NULL;
	float weight = 0;
	DBTransform* transform = NULL;
	Point pivot;

	l--;
	while (k--) {
		bone = _armature->_boneList[k];
		boneName = bone->name;
		weigthLeft = 1;

		x = 0;
		y = 0;
		skewX = 0;
		skewY = 0;
		scaleX = 0;
		scaleY = 0;
		pivotX = 0;
		pivotY = 0;

		i = _animationLayer.size();
		while (i--) {
			layerTotalWeight = 0;
			animationStateList = _animationLayer[i];
			stateListLength = animationStateList.size();
			for (j = 0; j < stateListLength; j++) {
				animationState = animationStateList[j];
				if (k == l) {
					if (animationState->advanceTime(passedTime)) {
						removeState(animationState);
						j--;
						stateListLength--;
						continue;
					}
				}

				timelineState = animationState->_timelineStates[boneName];

				if (timelineState && timelineState->tweenActive) {
					weight = animationState->_fadeWeight * animationState->weight * weigthLeft;
					transform = timelineState->transform;
					pivot = timelineState->pivot;
					x += transform->x * weight;
					y += transform->y * weight;
					skewX += transform->skewX * weight;
					skewY += transform->skewY * weight;
					scaleX += transform->scaleX * weight;
					scaleY += transform->scaleY * weight;
					pivotX += pivot.x * weight;
					pivotY += pivot.y * weight;

					layerTotalWeight += weight;
				}
			}

			if (layerTotalWeight >= weigthLeft) {
				break;
			} else {
				weigthLeft -= layerTotalWeight;
			}
		}
		transform = bone->_tween;
		pivot = bone->_tweenPivot;

		transform->x = x;
		transform->y = y;
		transform->skewX = skewX;
		transform->skewY = skewY;
		transform->scaleX = scaleX;
		transform->scaleY = scaleY;
		pivot.x = pivotX;
		pivot.y = pivotY;
	}
}

void Animation::setActive(AnimationState* animationState, bool active) {
	if (active) {
		_isActive = true;
	} else {
		int i = _animationLayer.size();
		int j = 0;
		vector<AnimationState*> animationStateList;
		while (i--) {
			animationStateList = _animationLayer[i];
			j = animationStateList.size();
			while (j--) {
				if (animationStateList[j]->isPlaying) {
					return;
				}
			}
		}
		_isActive = false;
	}
}

unsigned int Animation::addLayer(unsigned int layer) {
	if (layer >= _animationLayer.size()) {
		layer = _animationLayer.size();
		_animationLayer.resize(layer + 1);
	}
	return layer;
}

void Animation::addState(AnimationState* animationState) {
	vector<AnimationState*> & animationStateList = _animationLayer[animationState->layer];
	animationStateList.push_back(animationState);
}

void Animation::removeState(AnimationState* animationState) {
	unsigned int layer = animationState->layer;
	vector<AnimationState*> & animationStateList = _animationLayer[layer];

	vector<AnimationState*>::iterator begin = animationStateList.begin();
	vector<AnimationState*>::iterator end = animationStateList.end();
	vector<AnimationState*>::iterator it = find(begin, end, animationState);

	if (it != end) {
		animationStateList.erase(it);
	}

	AnimationState::returnObject(animationState);

	if (animationStateList.empty() && layer == _animationLayer.size() - 1) {
		_animationLayer.pop_back();
	}
}
