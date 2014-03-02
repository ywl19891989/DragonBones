/*
 * Animation.h
 *
 *  Created on: 2014-3-2
 *      Author: Hali
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>
#include <vector>

using namespace std;

class Animation {
public:
	/**
	 * Creates a new Animation instance and attaches it to the passed Armature.
	 * @param	An Armature to attach this Animation instance to.
	 */
	Animation(Armature* armature);
	virtual ~Animation();

	static const string NONE;
	static const string SAME_LAYER;
	static const string SAME_GROUP;
	static const string SAME_LAYER_AND_GROUP;
	static const string ALL;

	/**
	 * Whether animation tweening is enabled or not.
	 */
	bool tweenEnabled;

	/**
	 * An vector containing all AnimationData names the Animation can play.
	 * @see dragonBones.objects.AnimationData.
	 */
	vector<string> & getMovementList();

	/**
	 * The name of the last AnimationData played.
	 * @see dragonBones.objects.AnimationData.
	 */
	string getMovementID();

	/**
	 * The last AnimationData this Animation played.
	 * @see dragonBones.objects.AnimationData.
	 */
	AnimationState* getLastAnimationState();

	/**
	 * An vector containing all AnimationData names the Animation can play.
	 * @see dragonBones.objects.AnimationData.
	 */
	vector<string> & getAnimationList();

	bool getIsPlaying();
	bool getIsComplete();

	/**
	 * The AnimationData list associated with this Animation instance.
	 * @see dragonBones.objects.AnimationData.
	 */
	vector<AnimationData*> & getAnimationDataList();
	void setAnimationDataList(vector<AnimationData*> & value);

	/**
	 * The amount by which passed time should be scaled. Used to slow down or speed up animations. Defaults to 1.
	 */
	float getTimeScale();
	void setTimeScale(float value);

	/**
	 * Qualifies all resources used by this Animation instance for garbage collection.
	 */
	void dispose();

	/**
	 * Move the playhead to that AnimationData
	 * @param animationName The name of the AnimationData to play.
	 * @param fadeInTime A fade time to apply (> 0)
	 * @param duration The duration of that AnimationData.
	 * @param loop Loop(0:loop forever, 1~+¡Þ:loop times, -1~-¡Þ:will fade animation after loop complete).
	 * @param layer The layer of the animation.
	 * @param group The group of the animation.
	 * @param fadeOutMode Fade out mode.
	 * @param displayControl Display control.
	 * @param pauseFadeOut Pause other animation playing.
	 * @param pauseFadeIn Pause this animation playing before fade in complete.
	 * @see dragonBones.objects.AnimationData.
	 * @see dragonBones.animation.AnimationState.
	 */
	AnimationState* gotoAndPlay(
			string animationName,
			float fadeInTime = -1,
			float duration = -1,
			float loop = -1,
			unsigned int layer = 0,
			string group = string(""),
			string fadeOutMode = SAME_LAYER_AND_GROUP,
			bool displayControl = true,
			bool pauseFadeOut = true,
			bool pauseFadeIn = true
	);

	/**
	 * Play the animation from the current position.
	 */
	void play();

	void stop();

	/**
	 * Returns the AnimationState named name.
	 * @return A AnimationState instance.
	 * @see dragonBones.animation.AnimationState.
	 */
	AnimationState* getState(string name, unsigned int layer = 0);

	bool hasAnimation(string animationName);

	void advanceTime(float passedTime);

	void setActive(AnimationState* animationState, bool active);

protected:
	vector<vector<AnimationState*>> _animationLayer;

private:
	Armature* _armature;
	bool _isActive;

	vector<string> _animationList;
	AnimationState* _lastAnimationState;
	bool _isPlaying;

	vector<AnimationData*> _animationDataList;

	float _timeScale;

	unsigned int addLayer(unsigned int layer);

	void addState(AnimationState* animationState);
	void removeState(AnimationState* animationState);
};

#endif /* ANIMATION_H_ */
