#pragma once
#include "Drawable.h"
#include "Synthesizer.h"
#include "Graphics.h"

class Piano : public Drawable 
{
public:
	void Draw(SDL_Renderer* renderer) override;
	void SetPosition(int x, int y) override;
};