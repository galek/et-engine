/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#include <et/core/tools.h>
#include <et/app/backgroundthread.h>

using namespace et;

BackgroundRunLoop::BackgroundRunLoop() :
	_owner(nullptr) { }

void BackgroundRunLoop::setOwner(BackgroundThread* owner)
	{ _owner = owner; }

void BackgroundRunLoop::addTask(Task* t, float delay)
{
	updateTime(queryContiniousTimeInMilliSeconds());
	RunLoop::addTask(t, delay);
	_owner->resume();
}

BackgroundThread::BackgroundThread()
{
	_runLoop.setOwner(this);
}

ThreadResult BackgroundThread::main()
{
	while (running())
	{
		if (_runLoop.hasTasks() || _runLoop.firstTimerPool()->hasObjects())
		{
			_runLoop.update(queryContiniousTimeInMilliSeconds());
			Thread::sleepMSec(1);
		}
		else
		{
			suspend();
		}
	}
	
	return 0;
}
