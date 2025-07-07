#include <iostream>
#include "AppWindow.h"

using namespace std;

int main() {

	cout << "Hello Game Engine" << endl;

	AppWindow app;
	if (app.init()) {
		while(app.isRun()) {
			app.broadcast();
		}
	}
}



