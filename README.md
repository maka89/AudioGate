# AudioGate
Implementation of a Noise Gate for audio applications
https://www.mathworks.com/help/audio/ref/noisegate.html

## Usage
```c++
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
```
