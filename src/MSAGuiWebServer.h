#ifndef __OFXWEBSIMPLEGUITOO__
#define __OFXWEBSIMPLEGUITOO__

#include "ofMain.h"
#include "ofxWebServer.h"
#include "MSAGui.h"


namespace MSA {
	class GuiWebServer: public Gui, public ofxWSRequestHandler {
	public:
		GuiWebServer();
		void startServer(int port = 8910);
		void stopServer();
		
		void httpGet(string url);
		/*
		 // pasted from GuiToo
		 GuiPage		&addPage(string name = "");
		 GuiControl		&addControl(GuiControl& control);
		 GuiContent		&addContent(string name, ofBaseDraws &content, float fixwidth = -1);
		 GuiButton		&addButton(string name, bool &value);
		 GuiFPSCounter	&addFPSCounter();
		 //	GuiMovieSlider	&addMovieSlider(string name, ofVideoPlayer& input);
		 GuiQuadWarp	&addQuadWarper(string name, ofPoint *pts);
		 GuiSliderInt	&addSlider(string name, int &value, int min, int max);
		 GuiSliderFloat	&addSlider(string name, float &value, float min, float max, float smoothing = 0);
		 GuiSlider2d	&addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax);
		 GuiTitle		&addTitle(string name);
		 GuiToggle		&addToggle(string name, bool &value);
		 */
	private:
		ofxWebServer server;
		string describePage(GuiPage *page);
		string describeControl(GuiControl *control);
		GuiControl *findControlByName(string name);
	};
#endif // __OFXWEBSIMPLEGUITOO__
}