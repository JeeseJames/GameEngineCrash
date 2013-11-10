#include "ResourceManager.h"
#include "GameManager.h"
#include "MeshResource.h"
#include "PathResource.h"
#include "AudioResource.h"
#include "FontResource.h"
#include "CursorResource.h"
#include "DocumentResource.h"
#include "ErrorLogManager.h"
#include "TinyXML.h"

ResourceManager::ResourceManager(GameManager* gm)
{
   game_manager = gm;
   current_group = "";
   all_resources = new TableAVL<ListArrayID<GameResource>, String >(&ListArrayID<GameResource>::compare_items, &ListArrayID<GameResource>::compare_keys);
}

ResourceManager::~ResourceManager()
{
   AVLTreeIterator<ListArrayID<GameResource> >* all_lists_iter = all_resources->tableIterator();

   while(all_lists_iter->hasNext())
   {
      ListArrayID<GameResource>* list = all_lists_iter->next();
      ListArrayIterator<GameResource>* list_iter = list->iterator();

      while(list_iter->hasNext())
      {
         GameResource* resource = list_iter->next();
         delete resource;
      }

      delete list_iter;
      delete list;
   }

   delete all_lists_iter;
   delete all_resources;
}

void ResourceManager::loadResources(std::string group_name)
{
   if (current_group == group_name) return;
   if (current_group != "") unloadResources();
   
   game_manager->loadRocket(group_name);

   String* key = new String(group_name.c_str());
   ListArrayID<GameResource>* list = all_resources->tableRetrieve(key);
	
   ListArrayIterator<GameResource>* iter = list->iterator();
   //make sure that the PATHs are all loaded first
   while(iter->hasNext())
   {
      GameResource* resource = iter->next();
	  if(resource->getResourceType() == PATH)
	  {
		resource->load();
	  }
   }

   delete iter;
   
   //load the Rocket FONTs next
   iter = list->iterator();
    while(iter->hasNext())
   {
      GameResource* resource = iter->next();
      if (resource->getResourceType() == FONT)
      {
         resource->load();
      }
   }
   delete iter;
   
    //load the rest
   iter = list->iterator();
   while(iter->hasNext())
   {
      GameResource* resource = iter->next();
      GameResourceType grt = resource->getResourceType();
      if (grt != PATH && grt != FONT)
      {
         resource->load();
      }
   }
   delete iter;
   std::string meshesLoaded = "Meshes should all be loaded";
   cout << meshesLoaded << endl;
   game_manager->logProgress(meshesLoaded);
   
   delete key; 
   
   //initialize and load the Ogre group
   game_manager->initialiseRenderResourceGroup(group_name);
   game_manager->loadRenderResourceGroup(group_name);
   
   current_group = group_name;
}

void ResourceManager::unloadResources()
{
   std::string group_name = current_group;

   String* key = new String(group_name.c_str());
   ListArrayID<GameResource>* list = all_resources->tableRetrieve(key);  //old scope

   ListArrayIterator<GameResource>* iter = list->iterator();
   while(iter->hasNext())
   {
      GameResource* resource = iter->next();       
      resource->unload();
   }

   delete iter;
   delete key;

  game_manager->unloadRocket();
   game_manager->unloadRenderResourceGroup(group_name);
   current_group = "";
}


GameResource* ResourceManager::findResourceByID(unsigned int resource_id)
{
   if (current_group == "") return NULL;

   String* key = new String(current_group.c_str());
   ListArrayID<GameResource>* current_list = all_resources->tableRetrieve(key);
   delete key;
   ListArrayIterator<GameResource>* current_list_iter = current_list->iterator();

   while(current_list_iter->hasNext())
   {
      GameResource* game_resource = current_list_iter->next();
      int test_resource_id = game_resource->getResourceID();

      if (test_resource_id == resource_id)
      {
         delete current_list_iter;
         return game_resource;
      }
   }
   delete current_list_iter;

   return NULL;  //the requested resource_id was not found
}

void ResourceManager::loadFromXMLFile(std::string file_name)
{
   int resource_count = 0;

   TiXmlDocument doc(file_name.c_str());
   if (doc.LoadFile())
   {
      TiXmlNode* resource_tree = doc.FirstChild("resources");
      if (resource_tree)
      {
         //Enumerate resource objects (eventually, child will be false and loop will terminate)
         for(TiXmlNode* child = resource_tree->FirstChild(); child; child = child->NextSibling())
         {
            TiXmlElement* resource_element = child->ToElement();
            if(resource_element)
            {
               GameResource* game_resource = NULL;

               TiXmlElement* uid_element = (TiXmlElement*) resource_element->FirstChild("uid");
               unsigned int uid = atoi(uid_element->GetText());
               TiXmlElement* type_element = (TiXmlElement*) resource_element->FirstChild("resource_type");
               std::string resource_type = type_element->GetText();
               TiXmlElement* filename_element = (TiXmlElement*) resource_element->FirstChild("file_name");
               std::string file_name = filename_element->GetText();
               TiXmlElement* scope_element = (TiXmlElement*) resource_element->FirstChild("scope");
               std::string scope = scope_element->GetText();
				
				if (resource_type == "audio")  //audio elements have an additional field, audio_type
               {
                  TiXmlElement* audio_element = (TiXmlElement*) resource_element->FirstChild("audio_type");
                  std::string audio_type = audio_element->GetText();
                  if (audio_type == "stream")
                  {
                     game_resource = new AudioResource(uid, scope, file_name, AUDIO, STREAM, game_manager);
                  }
                  else
                  {
                     game_resource = new AudioResource(uid, scope, file_name, AUDIO, SAMPLE, game_manager);
                  }
               }
               else if (resource_type == "path")
               {
                  game_resource = new PathResource(uid, scope, file_name, PATH, game_manager);
               }
               else if (resource_type == "mesh")
               {
                  game_resource = new MeshResource(uid, scope, file_name, MESH, game_manager);
               }
			   else if (resource_type == "font")
               {
                  game_resource = new FontResource(uid, scope, file_name, FONT, game_manager);
               }
               else if (resource_type == "cursor")
               {
                  game_resource = new CursorResource(uid, scope, file_name, CURSOR, game_manager);
               }
               else if (resource_type == "document")
               {
                  game_resource = new DocumentResource(uid, scope, file_name, DOCUMENT, game_manager);
               }

               if (game_resource)
               {
                  String* key = new String(scope.c_str());
                  ListArrayID<GameResource>* list = all_resources->tableRetrieve(key);  //place in the appropriate list
                  if (list)
                  {
                     list->add(game_resource);
                     delete key;
                  }
                  else
                  {
                     list = new ListArrayID<GameResource>(key);
                     list->add(game_resource);
                     all_resources->tableInsert(list);
                  }
                  resource_count++;
               }
            }  //individual resource element
            else 
            {
               std::string str = "Resource manager failed to load resource meta data ";
               str.append("" + (resource_count+1));
               str.append(".");
               THROW_EXCEPTION(2, str);
            }

         }  //resource elements for loop

      }  //resource tree
      else 
      {
         THROW_EXCEPTION(1, "Resource manager failed to load any resources.");
      }

   }  //document
   else 
   {
      THROW_EXCEPTION(1, "Resource manager failed to find the resource metadata file.");
   }
   std::string str = "Resources loaded from " + file_name;
   game_manager->logProgress(str);
}
