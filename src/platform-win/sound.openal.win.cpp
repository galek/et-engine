/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#include <et/sound/sound.h>

#if (ET_PLATFORM_WIN)

void et::audio::Manager::nativeInit() { }
void et::audio::Manager::nativeRelease() { }

void et::audio::Manager::nativePreInit() { }
void et::audio::Manager::nativePostRelease() { }

#endif
