/*
 *  Gui.cpp
 *  ofxWebSimpleGuiTooExample
 *
 *  Created by Marek Bereza on 27/03/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "MSAGui.h"

#ifdef MSAGUI_WEBSERVER

namespace MSA {
	void GuiWebServer::startServer(int port) {
		server.start("GuiWebServer", port);
		server.addHandler(this, "/control");
	}
	
	void Gui::stopServer(){
		server.stop();
	}
	void Gui::httpGet(string url) {
		
		string key = getRequestParameter("key");
		if(key=="") {
			string guiDesc = "[";
			for(int i = 0; i < pages.size(); i++) {
				guiDesc += describePage(pages[i]);
				if(i+1<pages.size()) {
					guiDesc += ",";
				}
			}
			guiDesc += "]";
			httpResponse(guiDesc);
		} else {
			
			string value = getRequestParameter("value");
			printf("value received: %s = %s\n", key.c_str(), value.c_str());
			GuiControl *ctrl = &control(key);
			if(ctrl!=NULL) {
				if(ctrl->controlType=="Toggle") {
					GuiToggle *t = (GuiToggle*)ctrl;
					*(t->value) = (value=="true");
				} else if(ctrl->controlType=="SliderInt") {
					GuiSliderInt *t = (GuiSliderInt*)ctrl;
					*(t->value) = atoi(value.c_str());
				} else if(ctrl->controlType=="SliderFloat") {
					GuiSliderFloat *t = (GuiSliderFloat*)ctrl;
					*(t->value) = atof(value.c_str());
				} else if(ctrl->controlType=="Button") {
					GuiToggle *t = (GuiToggle*)ctrl;
					//				t->onPress(0, 0, 0);
					//				t->onRelease(0, 0, 0);
					*(t->value) = true;
					// 				printf("Hello here!!\n");
				}
			}
			httpResponse("thanks");
		}
	}
	
	string Gui::describePage(GuiPage *page) {
		string desc = "{\"name\": \""+page->name+"\", \"controls\":[";
		for(int i = 0; i < page->getControls().size(); i++) {
			desc += describeControl(page->getControls()[i]);
			if(i+1<page->getControls().size()) {
				desc += ",";
			}
		}
		desc += "]}";
		return desc;
	}
	string Gui::describeControl(GuiControl *ctrl) {
		string desc = "{\"name\":\""+ctrl->name + "\",";
		desc += "\"type\": \""+ctrl->controlType+"\"";
		
		if(ctrl->controlType=="Toggle") {
			GuiToggle *t = (GuiToggle*)ctrl;
			if(*t->value) desc += ", \"value\":\"true\"";
			else desc += ", \"value\":\"false\"";
		} else if(ctrl->controlType=="SliderInt") {
			GuiSliderInt *t = (GuiSliderInt*)ctrl;
			desc += ", \"value\":\""+ofToString(*(t->value))+"\"";
			desc += ", \"min\":\""+ofToString(t->min)+"\"";
			desc += ", \"max\":\""+ofToString(t->max)+"\"";
			
		} else if(ctrl->controlType=="SliderFloat") {
			GuiSliderFloat *t = (GuiSliderFloat*)ctrl;
			desc += ", \"value\":\""+ofToString(*(t->value))+"\"";
			desc += ", \"min\":\""+ofToString(t->min)+"\"";
			desc += ", \"max\":\""+ofToString(t->max)+"\"";
			
		}
		desc += "}";
		return desc;
	}
}
#endif