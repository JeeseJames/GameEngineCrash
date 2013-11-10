AutomatedMakefile = am
CC = g++
GAME_PATH = C:

INC_DIRS=-I./ -I$(GAME_PATH)/Ogre/include/Ogre/ -I$(GAME_PATH)/Ogre/boost/  -I./OIS/include/OIS/ -I./TinyXML/ -I./Bass/ -I./libRocket/include/ 
LIB_DIRS=-L./ -L$(GAME_PATH)/Ogre/lib/Release/ -L$(GAME_PATH)/Ogre/boost/lib/ -L./OIS/lib/ -L./TinyXML/ -L./Bass/ -L./libRocket/lib/ -L./CSC2110/
LIBS=-lOgreMain -lboost_system-mgw47-mt-1_51 -ltinyxml -lCSC2110 -lOIS -lbass -lRocketCore -lRocketControls -lRocketDebugger

COMPILE = $(CC) $(INC_DIRS) -w -c
LINK = $(CC) $(LIB_DIRS) -o

all: Ogre

Ogre:   RenderListener.o RenderManager.o GameException.o ErrorLogManager.o GameManager.o ResourceManager.o GameResource.o MeshResource.o PathResource.o KeyPressBehavior.o KeyReleaseBehavior.o KeyHeldBehavior.o MousePressBehavior.o MouseReleaseBehavior.o MouseMoveBehavior.o MouseHeldBehavior.o InputManager.o BehaviorManager.o KeyState.o AudioPlayer.o AudioManager.o AudioResource.o GUIManager.o FontResource.o CursorResource.o DocumentResource.o RenderInterfaceOgre3D.o SystemInterfaceOgre3D.o AudioManager.o Main.o
	$(LINK) Game.exe RenderListener.o RenderManager.o GameException.o ErrorLogManager.o GameManager.o ResourceManager.o GameResource.o MeshResource.o PathResource.o KeyPressBehavior.o KeyReleaseBehavior.o KeyHeldBehavior.o MousePressBehavior.o MouseReleaseBehavior.o MouseMoveBehavior.o MouseHeldBehavior.o InputManager.o BehaviorManager.o KeyState.o  AudioPlayer.o AudioResource.o GUIManager.o FontResource.o CursorResource.o DocumentResource.o RenderInterfaceOgre3D.o SystemInterfaceOgre3D.o AudioManager.o Main.o $(LIBS)

GameException.o:	GameException.h GameException.cpp
			$(COMPILE) GameException.cpp

ErrorLogManager.o:	ErrorLogManager.h ErrorLogManager.cpp
			$(COMPILE) ErrorLogManager.cpp

RenderManager.o:	RenderManager.h RenderManager.cpp
			$(COMPILE) RenderManager.cpp

RenderListener.o:	RenderListener.h RenderListener.cpp
			$(COMPILE) RenderListener.cpp

GameManager.o:		GameManager.h GameManager.cpp
			$(COMPILE) GameManager.cpp

ResourceManager.o:  ResourceManager.h ResourceManager.cpp
			$(COMPILE) ResourceManager.cpp

GameResource.o:     GameResource.h GameResource.cpp
			$(COMPILE) GameResource.cpp
			
MeshResource.o:     MeshResource.h MeshResource.cpp
			$(COMPILE) MeshResource.cpp
			
PathResource.o:     PathResource.h PathResource.cpp
			$(COMPILE) PathResource.cpp
			
KeyPressBehavior.o:  KeyPressBehavior.h KeyPressBehavior.cpp
			$(COMPILE) KeyPressBehavior.cpp
		
KeyReleaseBehavior.o:  KeyReleaseBehavior.h KeyReleaseBehavior.cpp
			$(COMPILE) KeyReleaseBehavior.cpp
			
KeyHeldBehavior.o:     KeyHeldBehavior.h  KeyHeldBehavior.cpp
			$(COMPILE) KeyHeldBehavior.cpp
			
MousePressBehavior.o:  MousePressBehavior.h MousePressBehavior.cpp
			$(COMPILE) MousePressBehavior.cpp
			
MouseMoveBehavior.o:  MouseMoveBehavior.h MouseMoveBehavior.cpp
			$(COMPILE)  MouseMoveBehavior.cpp
			
MouseReleaseBehavior.o: MouseReleaseBehavior.h MouseReleaseBehavior.cpp
			$(COMPILE) MouseReleaseBehavior.cpp
			
MouseHeldBehavior.o:  MouseHeldBehavior.h MouseHeldBehavior.cpp
			$(COMPILE) MouseHeldBehavior.cpp
			
BehaviorManager.o:		  BehaviorManager.h  BehaviorManager.cpp
			$(COMPILE)  BehaviorManager.cpp

KeyState.o:			  KeyState.h KeyState.cpp
			$(COMPILE) KeyState.cpp

InputManager.o:  InputManager.h InputManager.cpp
			$(COMPILE)  InputManager.cpp
			
AudioManager.o:		AudioManager.h AudioManager.cpp
			$(COMPILE) AudioManager.cpp
		
AudioResource.o:	AudioResource.h AudioResource.cpp
			$(COMPILE) AudioResource.cpp
			
AudioPlayer.o:		AudioPlayer.h AudioPlayer.cpp
			$(COMPILE) AudioPlayer.cpp
			
GUIManager.o: GUIManager.h GUIManager.cpp
			$(COMPILE) GUIManager.cpp
			
FontResource.o: FontResource.h FontResource.cpp
			$(COMPILE) FontResource.cpp
			
CursorResource.o: CursorResource.h CursorResource.cpp
			$(COMPILE) CursorResource.cpp
		
DocumentResource.o: DocumentResource.h DocumentResource.cpp
			$(COMPILE) DocumentResource.cpp
			
RenderInterfaceOgre3D.o: RenderInterfaceOgre3D.h RenderInterfaceOgre3D.cpp
			$(COMPILE) RenderInterfaceOgre3D.cpp
	
SystemInterfaceOgre3D.o: SystemInterfaceOgre3D.h SystemInterfaceOgre3D.cpp
			$(COMPILE) SystemInterfaceOgre3D.cpp
			




Main.o:			Main.cpp
			$(COMPILE) Main.cpp

clean:     
			rm -rf GameException.o
			rm -rf ErrorLogManager.o
			rm -rf RenderManager.o
			rm -rf RenderListener.o
			rm -rf GameManager.o
			rm -rf ResourceManager.o
			rm -rf GameResource.o
			rm -rf MeshResource.o
			rm -rf PathResource.o
			rm -rf KeyPressBehavior.o
			rm -rf KeyReleaseBehavior.o
			rm -rf MousePressBehavior.o
			rm -rf MouseReleaseBehavior.o
			rm -rf MouseMoveBehavior.o
			rm -rf MouseHeldBehavior.o
			rm -rf InputManager.o
			rm -rf BehaviorManager.o
			rm -rf KeyState.o
			rm -rf Main.o
			rm -rf Ogre.log
			rm -rf GameLog.txt
			rm -rf Game.exe
			cls