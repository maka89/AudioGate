# AudioGate
Implementation of a Noise Gate for audio applications
https://www.mathworks.com/help/audio/ref/noisegate.html

## Usage
```c++
#include <gate.hpp>
vector<double> x = getTestTone();
vector<double> y = vector<double>();

BasicGate g;
g.setFs(48000.0); // Set Sample Freq. [Hz]
g.setAttack(100.0); // Set Attack (This equals gate CLOSING) [ms]
g.setRelease(5.0); // Set Release (Gate opening) [ms]
g.setFloor(-16.0); // Turn down volume by this amount when closed [dB].
g.setThreshold(-12.0); // Threshold [dB]
g.setHold(50.0); //Hold [ms]
g.setDbScale(false); // Wether to use dB or linear scale. Will change the shape of gain envelope a bit when gate is opening/closing. 
g.reset(); // Reset buffers.


for (int i = 0; i < x.size(); i++) {
  double tmp;
  tmp = g.calc_gain(x[i]);
  y.push_back(tmp);
}
printData(x, y,"stepGate.txt");
```
