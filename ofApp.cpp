#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofSetCircleResolution(72);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 20, true, true, true);
	this->word = "0123";
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSeedRandom(39);

	ofNoFill();
	ofSetColor(200);
	for (int i = 0; i < this->word.size(); i++) {

		auto radius = -240 + ofMap(ofNoise(i, ofGetFrameNum() * 0.05), 0, 1, -50, 100);
		ofDrawCircle(glm::vec2(), radius);
	}

	ofFill();
	ofSetColor(255);
	for (int i = 0; i < 72; i++) {

		auto location = glm::vec3(-25, -230, 0);

		int word_index = (int)ofRandom(this->word.size());
		ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			//outline[outline_index] = outline[outline_index].getResampledByCount(500);
			auto vertices = outline[outline_index].getVertices();
			for (auto& vertex : vertices) {

				float rotate_deg = i * 5;
				auto noise_location = glm::vec2(cos(rotate_deg * DEG_TO_RAD), sin(rotate_deg * DEG_TO_RAD)) * 30;

				glm::vec3 v = location + vertex;
				auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
				v = glm::vec4(v, 0) + glm::vec4(0, ofMap(ofNoise(word_index, ofGetFrameNum() * 0.05), 0, 1, -50, 100), 0, 0);
				v = glm::vec4(v, 0) * rotation;

				ofVertex(v);
			}
		}
		ofEndShape(true);
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}