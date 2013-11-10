#if !defined (RENDER_LISTENER)
#define RENDER_LISTENER

#include "Ogre.h"
#include "CSC2110/ListArray.h"

class RenderManager;

class RenderListener: public Ogre::FrameListener
{
   private:
      RenderManager* render_manager;
      bool render;
      ListArray<Ogre::AnimationState>* animation_states;

   public:
      RenderListener(RenderManager* render_manager);
      virtual ~RenderListener();

      void addAnimationState(Ogre::AnimationState* animation_state);

      //called as a new frame begins
      bool frameStarted(const Ogre::FrameEvent& event);

      //called after the back buffer is flipped and the scene is presented to the display
      bool frameRenderingQueued(const Ogre::FrameEvent& event);

      //called after the scene has rendered but before the back buffer is drawn
      bool frameEnded(const Ogre::FrameEvent& event);

      void stopRendering();
      void checkInput();
};

#endif
