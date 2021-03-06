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

#ifndef SPINE_COCOS2DX_H_
#define SPINE_COCOS2DX_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {

typedef struct {
	AtlasPage super;
	cocos2d::CCTexture2D* texture;
	cocos2d::CCTextureAtlas* atlas;
} Cocos2dxAtlasPage;

/**/

class CCSkeleton;

typedef struct {
	Skeleton super;
	CCSkeleton* node;
} Cocos2dxSkeleton;

class CCSkeleton: public cocos2d::CCNodeRGBA, public cocos2d::CCBlendProtocol {
public:
	Skeleton* skeleton;
	AnimationState* state;
	float timeScale;
	bool debugSlots;
	bool debugBones;
	cocos2d::CCTextureAtlas* atlas; // All region attachments for a skeleton must use the same texture.
	unsigned int quadCount;

	static CCSkeleton* create (SkeletonData* skeletonData, AnimationStateData* stateData = 0);
	CCSkeleton (SkeletonData* skeletonData, AnimationStateData* stateData = 0);
	virtual ~CCSkeleton ();

	virtual void update (float deltaTime);
	virtual void draw ();

	// CCBlendProtocol
	CC_PROPERTY(cocos2d::ccBlendFunc, blendFunc, BlendFunc);
};

/**/

typedef struct {
	RegionAttachment super;
	cocos2d::ccV3F_C4B_T2F_Quad quad;
	cocos2d::CCTextureAtlas* atlas;
} Cocos2dxRegionAttachment;

}

#endif /* SPINE_COCOS2DX_H_ */
