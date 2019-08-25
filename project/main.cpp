/*
 * main.cpp
 *
 *  Created on: 25 авг. 2019 г.
 *      Author: blabu
 */

#include <iostream>
#include "baseClass.hpp"
#include <dlfcn.h>

#include <list>
#include <dirent.h>
#include<cstdlib>

void findAllPlugins(const std::string& path, std::list<std::string>& pluginNames) {
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir(path.c_str()) ){
		while(entry = readdir(pDIR)){
			std::string file(entry->d_name);
			if( file.compare(".") > 0 && file.compare("..") > 0) {
				std::cout << file << std::endl;
				if(file.find(".so") != std::string::npos ) {
					pluginNames.push_back(std::move(file));
				}
			}
		}
		closedir(pDIR);
	} else {
		std::cout<< "Can not open dir: "<<path<<std::endl;
	}
}
typedef struct {
	void *plugin;
	baseTest *test;
	deleteTest_T *del;
} task;

int main() {
	const std::string pluginsPath("/path/to/plugin/folder");
	std::list<std::string> pluginNames;
	std::list<task> handlers;
	findAllPlugins(pluginsPath,pluginNames);

	for(auto name : pluginNames) {
		std::cout<<"Find plugin "<<name<<std::endl;
		void* plugin = dlopen((pluginsPath + "/" +  name).c_str(), RTLD_NOW);
	    if(!plugin) {
	        std::cout<<"Can not load library"<<dlerror()<<std::endl;
	        continue;
	    }
	    dlerror();
	    createTest_t* creator = reinterpret_cast<createTest_t*>(dlsym(plugin,"createTest"));
	    if(!creator) {
	        std::cout<<"Could not create Test "<<dlerror()<<std::endl;
	        dlclose(plugin);
	        continue;
	    }
	    dlerror();
	    deleteTest_T* del = reinterpret_cast<deleteTest_T*>(dlsym(plugin,"deleteTest"));
	    if(!del) {
	        std::cout<<"Could not delete Test "<<dlerror()<<std::endl;
	        dlclose(plugin);
	        continue;
	    }
	    task t;
	    t.plugin = plugin;
	    t.del = del;
	    t.test = creator();
	    handlers.push_back(std::move(t));
	}
	int i = 0;
	for(auto h : handlers) {
		h.test->PrintThis("Hello ");
		++i;
		std::cout<<h.test->sum(i,i+1)<<std::endl;
		h.del(h.test);
		dlclose(h.plugin);
	}
    return 0;
}
