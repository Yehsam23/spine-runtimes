/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <iostream>
#include <spine/spine-sfml.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace spine;
#include <stdio.h>
int main () {
	// Load atlas, skeleton, and animations.
	Atlas* atlas = Atlas_readAtlasFile("../data/spineboy.atlas");
	SkeletonJson* json = SkeletonJson_create(atlas);
	SkeletonData *skeletonData = SkeletonJson_readSkeletonDataFile(json, "../data/spineboy-skeleton.json");
	Animation* walkAnimation = SkeletonJson_readAnimationFile(json, "../data/spineboy-walk.json", skeletonData);
	Animation* jumpAnimation = SkeletonJson_readAnimationFile(json, "../data/spineboy-jump.json", skeletonData);
	SkeletonJson_dispose(json);

	// Configure mixing.
	AnimationStateData* stateData = AnimationStateData_create();
	AnimationStateData_setMix(stateData, walkAnimation, jumpAnimation, 0.4f);
	AnimationStateData_setMix(stateData, jumpAnimation, walkAnimation, 0.4f);

	SkeletonDrawable* drawable = new SkeletonDrawable(skeletonData, stateData);
	drawable->timeScale = 0.5f;
	Skeleton* skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	Skeleton_setToBindPose(skeleton);
	Skeleton_getRootBone(skeleton)->x = 320;
	Skeleton_getRootBone(skeleton)->y = 420;
	AnimationState_setAnimation(drawable->state, walkAnimation, true);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Spine SFML");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

		float delta = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		if (drawable->state->animation == walkAnimation) {
			if (drawable->state->time > 2) AnimationState_setAnimation(drawable->state, jumpAnimation, false);
		} else {
			if (drawable->state->time > 1) AnimationState_setAnimation(drawable->state, walkAnimation, true);
		}

		drawable->update(delta);

		window.clear();
		window.draw(*drawable);
		window.display();
	}

	Animation_dispose(walkAnimation);
	Animation_dispose(jumpAnimation);
	SkeletonData_dispose(skeletonData);
	Atlas_dispose(atlas);
}
