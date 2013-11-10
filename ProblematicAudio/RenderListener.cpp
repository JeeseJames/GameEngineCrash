#include "RenderListener.h"
#include "RenderManager.h"
using namespace Ogre;
#include "CSC2110/ListArrayIterator.h"

#include <iostream>
using namespace std;

void RenderListener::stopRendering()
{
   render = false;
}

RenderListener::RenderListener(RenderManager* rm)
{
   animation_states = new ListArray<Ogre::AnimationState>();
   render_manager = rm;
   render = true;
}

RenderListener::~RenderListener()
{
   delete animation_states;
   render_manager = NULL;
}

//Ogre notifies this class when frames are processed
//as long as this method returns true, the game will continue (automatically done by Ogre)

//FrameEvent is a struct containing the time since the last event, and the time since the last frame
bool RenderListener::frameStarted(const FrameEvent& event) 
{

   ListArrayIterator<Ogre::AnimationState>* anim_iter = animation_states->iterator();
   while(anim_iter->hasNext())
   {
      Ogre::AnimationState* animation_state = anim_iter->next();
      animation_state->addTime(event.timeSinceLastFrame);
   }
   delete anim_iter;


   render_manager->setTimeSinceLastFrame(event.timeSinceLastFrame);
   render_manager->checkInput();  //must be checked each and every frame
   return render;
}

bool RenderListener::frameEnded(const FrameEvent& event) {}
bool RenderListener::frameRenderingQueued(const FrameEvent& event) {}


void RenderListener::addAnimationState(AnimationState* anim_state)
{
   animation_states->add(anim_state);
}

