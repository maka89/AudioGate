#pragma once

#include "../src/gate.hpp"

#include <iostream>
#include <cstdlib>
#include "testutils.h"
using namespace std;


vector<double> getTestTone() {
	double fs = 48000.0;
	double freq = 400.0;
	double bef = 0.0;
	double len = 0.8;
	double after = 0.0;

	vector<double> levels;
	levels.push_back(-300.0);
	levels.push_back(-6.0);
	levels.push_back(-300.0);


	vector<double> x = genTestToneSteps(bef, after, len, fs, freq, levels);
	return x;
}
void stepGate() {

	vector<double> x = getTestTone();
	vector<double> y = vector<double>();

	BasicGate g;
	g.setFs(48000.0);
	g.setAttack(100.0);
	g.setRelease(5.0);
	g.setFloor(-16.0);
	g.setThreshold(-12.0);
	g.setHold(50.0);
	g.setDbScale(false);
	g.reset();


	for (int i = 0; i < x.size(); i++) {
		double tmp;
		tmp = g.calc_gain(x[i]);
		y.push_back(tmp);
	}
	printData(x, y,"stepGate.txt");

}

int main() {

	stepGate();
}
