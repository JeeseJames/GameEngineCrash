#include "RenderManager.h"
#include "GameManager.h"
#include "ErrorLogManager.h"

using namespace Ogre;
using namespace std;

/*void RenderManager::addResourceLocation(std::string file_name, std::string path_type, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.addResourceLocation(file_name, path_type, group_name);
}*/

void RenderManager::toggleLightSource(std::string light_name)
{
	Ogre::Light* light = scene_manager->getLight(light_name);
	if(light)
	{
	light->setVisible(! light->isVisible() );
	}
} 

void RenderManager::turnLightSourceOn(std::string light_name)
{
	Ogre::Light* light = scene_manager->getLight(light_name);
	
	if(light)
	{
		light->setVisible(true);
	}
}

void RenderManager::resetTransformNode(std::string node_name)
{
	SceneNode* node = scene_manager->getSceneNode(node_name);
}

void RenderManager::turnLightSourceOff(std::string light_name)
{
	Ogre::Light* light = scene_manager->getLight(light_name);
	
	if(light)
	{
		light->setVisible(false);
	}
}

void RenderManager::viewportDimensionsChanged(Ogre::Viewport *vp)
{
	  float actual_width = Ogre::Real(vp->getActualWidth());
      float actual_height = Ogre::Real(vp->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);
	  window->resize(actual_width,actual_height);
}

 void RenderManager::windowResized(Ogre::RenderWindow *rw)
 {
	int w = rw->getWidth();
	int h = rw->getHeight();
	gui_manager->windowResized(w,h);
	cout<<"RESIZED "<<w<<" x "<<h;
 }
 
 bool RenderManager::windowClosing(Ogre::RenderWindow *rw)
 {cout<<"NOPE";return false;}
 /*
void RenderManager::declareResource(std::string file_name, std::string mesh_str, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.declareResource(file_name, mesh_str, group_name);
}*/

void RenderManager::updateCameraRotation(float _yaw, float _pitch)
{
   camera->yaw(Degree(_yaw)*time_since_last_frame*-1);
   camera->pitch(Degree(_pitch)*time_since_last_frame*-1);
}

void RenderManager::setTimeSinceLastFrame(Real tslf)
{
   time_since_last_frame = tslf;
}

void RenderManager::updateCameraPosition(float x, float y, float z)
{
   camera->moveRelative(Vector3(x*time_since_last_frame, y*time_since_last_frame, z*time_since_last_frame));
}

size_t RenderManager::getWindowHandle()
{
   return window_handle;
}

int RenderManager::getWindowWidth()
{
   return viewport->getActualWidth();
}

int RenderManager::getWindowHeight()
{
   return viewport->getActualHeight();
}

void RenderManager::checkInput()
{
   game_manager->checkInput();
}

void RenderManager::updateAudio()
{
   //game_manager->updateAudio();
}

void RenderManager::initialiseResourceGroup(std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.initialiseResourceGroup(group_name);  //pre-load the resources located in the specific paths (parse scripts)
}

void RenderManager::loadResourceGroup(std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.loadResourceGroup(group_name, true, true);  //load the resources in the specific paths
}

void RenderManager::unloadResourceGroup(std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.destroyResourceGroup(group_name);   //completely remove resource information (could use clear instead of destroy)
}

void RenderManager::addPathResource(std::string file_name, std::string path_type, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.addResourceLocation(file_name, path_type, group_name);
}
      
void RenderManager::addMeshResource(std::string file_name, std::string mesh_str, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.declareResource(file_name, mesh_str, group_name);
}

void RenderManager::stopRendering()
{
   //stop rendering somehow
   render_listener->stopRendering();
}

void RenderManager::startRendering()
{
   root->addFrameListener(render_listener);  //now it is safe to start rendering
   root->startRendering();
}

RenderManager::RenderManager(GameManager* gm)
{
   game_manager = gm;
   time_since_last_frame = 0;
   gui_manager = new GUIManager(this);
   rocket_enabled = false;
}

RenderManager::~RenderManager()
{
   delete render_listener;
   delete root;

   root = NULL;
   game_manager = NULL;
}

void RenderManager::initOgre()
{
   root = NULL;
   window = NULL;
   scene_manager = NULL;

   camera = NULL;
   viewport = NULL;
 
   try
   {
      root = OGRE_NEW Root("","");  //resource/config files go here
      root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

      RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
      if (!render_system)
      {
         THROW_EXCEPTION(1, "OpenGL unavailable");
      }

      root->setRenderSystem(render_system);

      //manually set configuration options
      render_system->setConfigOption("Full Screen", "No");
      render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

      //initialize render system
      //automatically create and display the window, and give it a title
      window = root->initialise(true, "James McCoy's Most Awesome Game");  

      //can create BSP or octree scene managers
      scene_manager = root->createSceneManager(ST_GENERIC, "Default Scene Manager");
      window->getCustomAttribute("WINDOW", &window_handle);

      //the Ogre viewport corresponds to a clipping region into which the contents of the camera view will be rendered in the window on each frame
      //by default, the size of the viewport matches the size of the window, but the viewport can be cropped
      //the camera represents a view into an existing scene and the viewport represents a region into which an existing camera will render its contents
      camera = scene_manager->createCamera("Camera");
      viewport = window->addViewport(camera, 0, 0, 0, 1.0, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

      float actual_width = Ogre::Real(viewport->getActualWidth());
      float actual_height = Ogre::Real(viewport->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);
	  render_listener = new RenderListener(this);
	  Ogre::WindowEventUtilities::addWindowEventListener(window,this);
	  viewport->addListener(this);
   }

   catch(Ogre::Exception& e)  //an Ogre Exception, rethrow GameException
   {
      THROW_EXCEPTION(1, e.getFullDescription());  //error number 1 refers to an initialization problem
   }
   game_manager->logProgress("OGRE Initiliazed");
}

/*void RenderManager::init()
{
   root = NULL;
   window = NULL;
   scene_manager = NULL;

   camera = NULL;
   viewport = NULL;

   try
   {
	  //current_group="";
	  
      root = OGRE_NEW Root("","");  //resource/config files go here
      root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

      RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
      if (!render_system)
      {
         THROW_EXCEPTION(1, "OpenGL unavailable");
      }

      root->setRenderSystem(render_system);

      //manually set configuration options
      render_system->setConfigOption("Full Screen", "No");
      render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

      //initialize render system
      //automatically create and display the window, and give it a title
      window = root->initialise(true, "James McCoy's Most Awesome Game");  

      //can create BSP or octree scene managers
      scene_manager = root->createSceneManager(ST_GENERIC, "Default Scene Manager");
      window->getCustomAttribute("WINDOW", &window_handle);

      //the Ogre viewport corresponds to a clipping region into which the contents of the camera view will be rendered in the window on each frame
      //by default, the size of the viewport matches the size of the window, but the viewport can be cropped
      //the camera represents a view into an existing scene and the viewport represents a region into which an existing camera will render its contents
      camera = scene_manager->createCamera("Camera");
      viewport = window->addViewport(camera, 0, 0, 0, 1.0, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

      float actual_width = Ogre::Real(viewport->getActualWidth());
      float actual_height = Ogre::Real(viewport->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);
	  render_listener = new RenderListener(this);  //careful: "this" must be valid
   }

   catch(Ogre::Exception& e)  //an Ogre Exception, rethrow GameException
   {
      THROW_EXCEPTION(1, e.getFullDescription());  //error number 1 refers to an initialization problem
   }
}
/*
void RenderManager::loadOgreResources(std::string group_name)
{
	//current_group = group_name;
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.initialiseResourceGroup(group_name);  //pre-load the resources located in the specific paths (parse scripts)
   rgm.loadResourceGroup(group_name, true, true);  //load the resources in the specific paths
}

void RenderManager::unloadOgreResources(std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.destroyResourceGroup(group_name);   //completely remove resource information (could use clear instead of destroy)
   //current_group = "";
}
*/
void RenderManager::rocketMouseMoved(float x_abs, float y_abs)
{
   gui_manager->rocketMouseMoved(x_abs, y_abs);
}

void RenderManager::rocketMousePressed(int mouse_x, int mouse_y, int button_id)
{
   gui_manager->rocketMousePressed(mouse_x, mouse_y, button_id);
}

void RenderManager::rocketMouseReleased(int mouse_x, int mouse_y, int button_id)
{
   gui_manager->rocketMouseReleased(mouse_x, mouse_y, button_id);
}

void RenderManager::loadRocketFont(std::string font_file_name, std::string group_name)
{
   gui_manager->loadRocketFont(font_file_name, group_name);
}

void RenderManager::loadRocketCursor(std::string cursor_file_name, std::string group_name)
{
   gui_manager->loadRocketCursor(cursor_file_name, group_name);
}

void RenderManager::loadRocketDocument(std::string doc_file_name, std::string group_name)
{
   gui_manager->loadRocketDocument(doc_file_name, group_name);
game_manager->logProgress("Rocket document loaded.");
}

void RenderManager::loadRocket(std::string current_group)
{
   gui_manager->loadRocket(current_group, getWindowWidth(), getWindowHeight());
   // Add the application as a listener to Ogre's render queue so we can render during the overlay.
   //scene_manager->addRenderQueueListener(this);
}

bool RenderManager::isRocketEnabled()
{
   return rocket_enabled;
}

void RenderManager::enableRocket()
{
   if (!rocket_enabled)
   {
      scene_manager->addRenderQueueListener(this);
      rocket_enabled = true;
   }
   else
   {
      scene_manager->removeRenderQueueListener(this);
      rocket_enabled = false;
   }
}

void RenderManager::unloadRocket()
{
   if (rocket_enabled)
   {
      scene_manager->removeRenderQueueListener(this);
   }
   gui_manager->unloadRocket();
}

// Called from Ogre before a queue group is rendered.
void RenderManager::renderQueueStarted(uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
{
   if (queueGroupId == Ogre::RENDER_QUEUE_OVERLAY && Ogre::Root::getSingleton().getRenderSystem()->_getViewport()->getOverlaysEnabled())
   {
      gui_manager->renderQueueStarted(getWindowWidth(), getWindowHeight());
   }
}

// Called from Ogre after a queue group is rendered.
void RenderManager::renderQueueEnded(uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation))
{
}

void RenderManager::buildSceneFromXML(std::string file_name)
{
 
   TiXmlDocument doc(file_name.c_str());
   if (doc.LoadFile())
   {
      TiXmlNode* scene_node = doc.FirstChild("default");//current_group.c_str());
      if (scene_node)
        {
         TiXmlNode* camera_node = scene_node->FirstChild("camera");

         std::string camera_position_text = GameManager::textFromChildNode(camera_node, "position");
         double* result = game_manager->parseDoubles(camera_position_text);
         Vector3 camera_position(result[0], result[1], result[2]);
         camera->setPosition(camera_position);
         delete[] result;

         std::string camera_look_at_text = GameManager::textFromChildNode(camera_node, "look_at");
         result = game_manager->parseDoubles(camera_look_at_text);
         Vector3 camera_look(result[0], result[1], result[2]);
         camera->lookAt(camera_look);
         delete[] result;

         std::string camera_clip_distance_text = GameManager::textFromChildNode(camera_node, "clip_distance");
         result = game_manager->parseDoubles(camera_clip_distance_text);
         camera->setNearClipDistance(result[0]);
         camera->setFarClipDistance(result[1]);
         delete[] result;

		 for(TiXmlNode* light_node = scene_node->FirstChild("light"); light_node; light_node = light_node->NextSibling("light"))
			{
			 

			 std::string light_name_text = GameManager::textFromChildNode(light_node, "name");
			 Light* light = scene_manager->createLight(light_name_text);
			 std::string light_type_text = GameManager::textFromChildNode(light_node, "type");
			 if (light_type_text == "directional")
			 {
				light->setType(Light::LT_DIRECTIONAL);
			 }
			 else
			 {
				light->setType(Light::LT_POINT);
			 }

			 std::string light_position_text = GameManager::textFromChildNode(light_node, "position");
			 result = GameManager::parseDoubles(light_position_text);
			 Vector3 light_pos(result[0], result[1], result[2]);
			 if (light_type_text == "directional")
			 {
				light->setDirection(light_pos);
			 }
			 else
			 {
				light->setPosition(light_pos);
			 }
			 delete[] result;

			 std::string light_color_text = GameManager::textFromChildNode(light_node, "color");
			 result = GameManager::parseDoubles(light_color_text);
			 light->setDiffuseColour(result[0], result[1], result[2]);
			 delete[] result;
			}
		}

      
	  TiXmlNode* scene_graph_node = scene_node->FirstChild("scene_graph");
	  if(scene_graph_node)
	  {
		TiXmlNode* root_node = scene_graph_node->FirstChild("root");
			if(root_node)
			{
				SceneNode* root_scene_node = scene_manager->getRootSceneNode();
				TiXmlNode* childrens_tree = scene_graph_node = root_node->FirstChild("children");
				if(childrens_tree)
				{
					buildChildren(childrens_tree, root_scene_node);
				}
				
			}
	  }
   }
   else
   {
      //set up a default camera and light source
   }

   //buildSubmarineSceneGraph();
   game_manager->logProgress("Scene loaded in from " + file_name);

}

void RenderManager::buildChildren(TiXmlNode* childrens_tree, SceneNode* parent_Node)
{
	if(!childrens_tree->FirstChild())
	{
		return; //Children tree has no child
	}
	else
	{
		for(TiXmlNode* child_node = childrens_tree->FirstChild(); child_node; child_node = child_node->NextSibling())
		{
			std::string child_name = GameManager::textFromChildNode(child_node, "name");
			SceneNode* sNode = scene_manager->createSceneNode(child_name);
			parent_Node->addChild(sNode);
			TiXmlNode* entity_node = child_node->FirstChild("entity");
			if(entity_node)
			{
				buildEntityNode(entity_node, sNode);//Build Entity Node
			}
			TiXmlNode* animation_node = child_node->FirstChild("animation");
			if(animation_node)
			{

				buildAnimationNode(animation_node, sNode); // Build Animation Node
			}
			double* result;
			std::string child_tra = GameManager::textFromChildNode(child_node, "translation");
			if(child_tra != "")
			{
			result = game_manager->parseDoubles(child_tra);
			Vector3 translate(result[0], result[1], result[2]);
			sNode->translate(translate, Node::TS_LOCAL);
			delete[] result;	
			}
			std::string child_rot = GameManager::textFromChildNode(child_node, "rotation");
			if(child_rot != "")
			{
				result = game_manager->parseDoubles(child_rot);
				Vector3 rotate(result[1], result[2], result[3]);
				sNode->rotate(Quaternion(result[0], result[1], result[2], result[3]), Node::TS_LOCAL);
				delete[] result;
			}
			
			std::string child_sca = GameManager::textFromChildNode(child_node, "scale");
			if(child_sca != "")
			{
				result = game_manager->parseDoubles(child_sca);
				Vector3 scale(result[0], result[1], result[2]);
				sNode->scale(scale);
				delete[] result;
			}
			sNode->setInitialState();
			TiXmlNode* childrens_tree = child_node->FirstChild("children");
			if(childrens_tree)
			{
				buildChildren(childrens_tree, sNode);
			}
			
		}
	}
}

void RenderManager::buildAnimationNode(TiXmlNode* animation_node, SceneNode* sNode)
{

	TiXmlNode* child_node = animation_node->FirstChild();
	std::string animation_name = GameManager::textFromChildNode(child_node, "name");
	std::string max_time_text = GameManager::textFromChildNode(child_node, "max");
	std::string loop = GameManager::textFromChildNode(child_node, "loop");
	std::string enabled = GameManager::textFromChildNode(child_node, "enabled");
	double* result = game_manager->parseDoubles(max_time_text);
	Ogre::Animation* animation = scene_manager->createAnimation(animation_name, result[0]);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	delete[] result;


	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(1, sNode);
	
	Ogre::TransformKeyFrame* key;
	
	for(child_node=child_node->NextSibling();child_node;child_node=child_node->NextSibling())
	{
		std::string key_frame = GameManager::textFromChildNode(child_node, "keyTime");
		std::string translation_text = GameManager::textFromChildNode(child_node, "translation");
		std::string rotation_text = GameManager::textFromChildNode(child_node,"rotation");
		std::string scale_text = GameManager::textFromChildNode(child_node, "scale");
		
		result = game_manager->parseDoubles(key_frame);
		key = track->createNodeKeyFrame(result[0]);
		delete[] result;

		
		if(translation_text!="")
		{
			result = game_manager->parseDoubles(translation_text);
			key->setTranslate(Vector3(result[0],result[1],result[2]));
			delete[] result;
		}
		
		if(rotation_text!="")
		{	
			result = game_manager->parseDoubles(rotation_text);
			
			key->setRotation(Ogre::Quaternion(Ogre::Degree(result[0]),Vector3(result[1],result[2],result[3])));
			delete[] result;
		}
		
		if(scale_text!="")
		{
			result = game_manager->parseDoubles(scale_text);
			key->setScale(Vector3(result[0],result[1],result[2]));
			delete[] result;
		}
		
	}
	Ogre::AnimationState* animation_state = scene_manager->createAnimationState(animation_name);
	
	if(enabled == "true")
	{
		animation_state->setEnabled(true);
	}
	else
	{
		animation_state->setEnabled(false);
	}
	if(loop == "true")
	{
		animation_state->setLoop(true);
	}
	else
	{
		animation_state->setLoop(false);
	}

	render_listener->addAnimationState(animation_state);

}

void RenderManager::buildEntityNode(TiXmlNode* entity_node, SceneNode* sNode)
{
	std::string entity_name = GameManager::textFromChildNode(entity_node, "name");
	std::string entity_mesh = GameManager::textFromChildNode(entity_node, "mesh");
	Ogre::Entity* entity = scene_manager->createEntity(entity_name, entity_mesh);
	std::string entity_material = GameManager::textFromChildNode(entity_node, "material");
	entity->setMaterialName(entity_material);
	sNode->attachObject(entity);
	
}

void RenderManager::updateTransformNode(std::string transform_node_name, TransformType transform, double xVal, double yVal, double zVal, double qVal) //Default value 0 for q, since will only be used for TransformType ROTATE
{
	SceneNode* transform_node = scene_manager->getSceneNode(transform_node_name); //does not have to be a transform node, but transforms will be appiled
	if(transform == TRANSLATE)
	{
		transform_node->translate(xVal*time_since_last_frame, yVal*time_since_last_frame, zVal*time_since_last_frame);		
	}
	else if(transform==ROTATE)
	{
		transform_node->rotate(Quaternion(Degree(qVal)*time_since_last_frame,Vector3(xVal, yVal, zVal)));	
	}
	else if(transform==SCALE)
	{
		transform_node->scale(xVal*time_since_last_frame,yVal*time_since_last_frame,zVal*time_since_last_frame);
	}
	else if(transform==INSTANT_TRANSLATE)
	{
		transform_node->translate(xVal,yVal,zVal); //An instant translate, I didn't like how time_since_last_frame honestly makes the translation unpredictable
	}
	else if(transform==INSTANT_ROTATE)
	{
		transform_node->rotate(Quaternion(Degree(qVal),Vector3(xVal,yVal,zVal)));
		//transform_node->rotate(Quaternion(qVal, xVal, yVal, zVal));
	}
	else if(transform==INSTANT_SCALE)
	{
		transform_node->scale(xVal,yVal,zVal);//instant implementation
	}
	else
	{
		//tranform of unknown type
		//affect nothing
	} 
}

void RenderManager::buildSubmarineSceneGraph()
{
   SceneNode* root_scene_node = scene_manager->getRootSceneNode();
   SceneNode* submarine_animation_node = scene_manager->createSceneNode("Submarine Animation Node");
   SceneNode* submarine_transform_node = scene_manager->createSceneNode("Submarine Transform Node");
   root_scene_node->addChild(submarine_animation_node);
   submarine_animation_node->addChild(submarine_transform_node);

   SceneNode* submarine_node = scene_manager->createSceneNode("Submarine Node");
   submarine_transform_node->addChild(submarine_node);

   Ogre::Entity* submarine_entity = scene_manager->createEntity("Submarine", "submarine.mesh");
   submarine_entity->setMaterialName("Submarine"); 
   submarine_node->attachObject(submarine_entity);

   submarine_node->yaw(Ogre::Degree(90), Node::TS_LOCAL);   //submarine built in right view
   submarine_node->pitch(Ogre::Degree(90), Node::TS_LOCAL); //this rotation applied first (Blender to Ogre)

   SceneNode* periscope_transform_node = scene_manager->createSceneNode("Periscope Transform Node");
   submarine_transform_node->addChild(periscope_transform_node);

   SceneNode* periscope_node = scene_manager->createSceneNode("Periscope Node");
   Ogre::Entity* periscope_entity = scene_manager->createEntity("Periscope", "periscope.mesh");
   periscope_entity->setMaterialName("Periscope"); 
   periscope_node->attachObject(periscope_entity);

   periscope_node->roll(Ogre::Degree(90), Node::TS_LOCAL);
   periscope_node->yaw(Ogre::Degree(90), Node::TS_LOCAL);
   periscope_node->pitch(Ogre::Degree(-90), Node::TS_LOCAL);
   periscope_node->scale(0.1,0.1,0.1);

   SceneNode* periscope_animation_node = scene_manager->createSceneNode("Periscope Animation Node");
   periscope_transform_node->addChild(periscope_animation_node);
   periscope_animation_node->addChild(periscope_node);

   periscope_transform_node->translate(Vector3(0,0.7,0), Node::TS_LOCAL);

   SceneNode* rudder_transform_node = scene_manager->createSceneNode("Rudder Transform Node");
   submarine_transform_node->addChild(rudder_transform_node);

   SceneNode* rudder_node = scene_manager->createSceneNode("Rudder Node");
   Ogre::Entity* rudder_entity = scene_manager->createEntity("Rudder", "rudder.mesh");
   rudder_entity->setMaterialName("Rudder"); 
   rudder_node->attachObject(rudder_entity);

   rudder_node->translate(-0.3,0,0, Node::TS_LOCAL);
   rudder_node->roll(Ogre::Degree(90), Node::TS_LOCAL);
   rudder_node->pitch(Ogre::Degree(90), Node::TS_LOCAL);
   rudder_node->scale(0.18,0.18,0.18);

   SceneNode* rudder_animation_node = scene_manager->createSceneNode("Rudder Animation Node");
   rudder_transform_node->addChild(rudder_animation_node);
   rudder_animation_node->addChild(rudder_node);

   rudder_transform_node->translate(-2.8,0.32,0);   

   SceneNode* propeller_transform_node = scene_manager->createSceneNode("Propeller Transform Node");
   submarine_transform_node->addChild(propeller_transform_node);

   SceneNode* propeller_node = scene_manager->createSceneNode("Propeller Node");
   Ogre::Entity* propeller_entity = scene_manager->createEntity("Propeller", "propeller.mesh");
   propeller_entity->setMaterialName("Propeller"); 
   propeller_node->attachObject(propeller_entity);

   propeller_node->yaw(Ogre::Degree(90), Node::TS_LOCAL);
   propeller_node->pitch(Ogre::Degree(90), Node::TS_LOCAL);
   propeller_node->scale(0.18,0.18,0.18);

   SceneNode* propeller_animation_node = scene_manager->createSceneNode("Propeller Animation Node");
   propeller_transform_node->addChild(propeller_animation_node);
   propeller_animation_node->addChild(propeller_node);

   propeller_transform_node->translate(-1.4,-0.8,0);
   //buildPropellerAnimation(propeller_animation_node);

   submarine_animation_node->translate(0,0,0, Node::TS_LOCAL);
   submarine_transform_node->rotate(Quaternion(Degree(45), Vector3(0,0,1)), Node::TS_LOCAL);
   
   cout<<"submarine_transform_node "<<submarine_transform_node->getOrientation()<<endl;
   cout<<"submarine_node"<<submarine_node->getOrientation()<<endl;
   cout<<"rudder_transform_node"<<rudder_transform_node->getOrientation()<<endl;
   cout<<"rudde_node"<<rudder_node->getOrientation()<<endl;
   cout<<"periscope_transform_node"<<periscope_transform_node->getOrientation()<<endl;
   cout<<"periscope_node"<<periscope_node->getOrientation()<<endl;
   cout<<"propeller_transform_node"<<propeller_transform_node->getOrientation()<<endl;
   cout<<"propeller_node"<<propeller_node->getOrientation()<<endl;

}

