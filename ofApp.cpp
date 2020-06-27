#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 80;
	int deg_span = 30;

	for (int x = 200; x <= ofGetWidth(); x += 320) {

		for (int y = 200; y <= ofGetHeight(); y += 320) {

			for (int deg = 0; deg < 360; deg += deg_span) {

				int next_deg = deg + deg_span;
				float noise_param = ofMap(ofNoise(glm::vec3(
					x + cos(deg * DEG_TO_RAD),
					y + sin(deg * DEG_TO_RAD),
					ofGetFrameNum() * 0.02)),
					0, 1, 0, 2);
				float next_noise_param = ofMap(ofNoise(glm::vec3(
					x + cos((deg + deg_span) * DEG_TO_RAD),
					y + sin((deg + deg_span) * DEG_TO_RAD),
					ofGetFrameNum() * 0.02)),
					0, 1, 2, 0);

				vector<glm::vec2> vertices;
				vertices.push_back(glm::vec2(
					x + radius * cos(deg * DEG_TO_RAD),
					y + radius * sin(deg * DEG_TO_RAD)));
				vertices.push_back(glm::vec2(
					x + (radius * noise_param) * cos((deg + deg_span * 0.25) * DEG_TO_RAD),
					y + (radius * noise_param) * sin((deg + deg_span * 0.25) * DEG_TO_RAD)));
				vertices.push_back(glm::vec2(
					x + (radius * next_noise_param) * cos((next_deg - deg_span * 0.25) * DEG_TO_RAD),
					y + (radius * next_noise_param) * sin((next_deg - deg_span * 0.25)* DEG_TO_RAD)));
				vertices.push_back(glm::vec2(
					x + radius * cos(next_deg * DEG_TO_RAD),
					y + radius * sin(next_deg * DEG_TO_RAD)));

				ofNoFill();
				ofSetLineWidth(2);
				ofBeginShape();
				ofVertex(vertices[0]);
				ofBezierVertex(vertices[1], vertices[2], vertices[3]);
				ofEndShape();

				ofFill();
				for (auto& vertex : vertices) {

					ofDrawCircle(vertex, 1.5);
				}

				ofSetLineWidth(1);
				ofDrawLine(vertices[0], vertices[1]);
				ofDrawLine(vertices[3], vertices[2]);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}