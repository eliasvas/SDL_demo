#pragma once
#include <util.h>
#include <memory>
#include <bitset>
#include <array>
#include <algorithm>
#include <vector>
#include <typeindex>
#include <typeinfo>



namespace engine {
	class Entity;
	class Component{
	public:
		Entity* entity;

		virtual void init(){}
		virtual void update(){}
		virtual void render(){}
		
		virtual ~Component(){}
	};

	class Entity{
	public:
		int foo = 10;
		bool active = true;
		std::vector<Component*> components;  //maybe unique_ptr<>, will see.
		bool isActive(){return active;}
		void destroy() {active = false;}
		template <typename T>
		bool hasComponent(){
			for (int i = 0; i < components.size(); i++){
				if (typeid(T) == typeid(*components[i]))return true;
			}
			return false;
		}
		template <typename T>
		Component* getComponent(){
			for (int i = 0; i < components.size(); i++){
				if (typeid(T) == typeid(*components[i]))return components[i];
			}
			return NULL;
		}
		template <typename T, typename... TArgs> 
		T& addComponent(TArgs&&... mArgs){
			T* cmp = new T(std::forward<TArgs>(mArgs)...);
			cmp->entity = this;
			components.push_back(cmp);
			cmp->init();
			return *cmp;
		}
		virtual void init(){}
		virtual void update(){
			for (int i = 0; i < components.size();++i){
				components[i]->update();	
			}
		}
		virtual void render(){
			for (int i =0; i < components.size();++i){
				components[i]->render();
			}
		}
	};

	struct EntityManager{
		std::vector<Entity*> entities;
		void update() {
			for(int i = 0; i < entities.size(); ++i){
				entities[i]->update();
			}
		}
		void render(){
			for(int i = 0; i < entities.size(); ++i){
				entities[i]->render();
			}

		}
		void refresh(){
			for (int i = 0; i < entities.size(); ++i){
				if (entities[i]->isActive() == false){
					entities.erase(entities.begin() + i); //TODO check
				}
			}
		}
		Entity* addEntity(Entity* e) {
			entities.push_back(e);
			return e;
		}
		Entity* addEntity() {
			Entity *e = new Entity();
			entities.push_back(e);
			return e;
		}
	};

	struct TransformComponent: public Component{
		TransformComponent(int x, int y): x(x), y(y){}
		int x;
		int y;
	};

}




