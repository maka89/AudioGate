#pragma once
#include <cmath>
#include <limits>
const double lowest_number = std::numeric_limits<double>::denorm_min();
inline double gain_to_db(const double& x) { return 20.0 * std::log10(x + lowest_number); }
inline double db_to_gain(const double& x) { return std::pow(10.0, x * 0.05); }

class BasicGate {
public:
	BasicGate() {
		this->setFs(48000.0);
		this->setAttack(1.0);
		this->setRelease(100.0);
		this->setFloor(-20.0);
		this->last_gain = 0.0;
		this->setThreshold(-40.0);
		this->setHold(100.0);
		this->setDbScale(false);
	}
	void setFs(double fs) { this->fs = fs;  recalcConstants(); } // Set Sample Freq
	void setAttack(double atk) { this->t_atk = atk;  recalcConstants();} // Set Attack
	void setRelease(double rlse) { this->t_rlse = rlse;  recalcConstants();} // Set Release
	void setHold(double hold) { this->t_hold = hold; } // Set Hold
	void setThreshold(double threshold) { this->threshold = db_to_gain(threshold); this->threshold_db = threshold; } // Set Threshold
	void setFloor(double floor) { this->floor = db_to_gain(floor); this->floor_db = floor; } // Set Floor
	void setDbScale(bool b) { this->log = b; reset(); }
	bool isDbScale() { return this->log; }
	void reset() { this->last_gain = isDbScale()? this->floor_db: this->floor; this->attack_counter = 0.0; } //Reset attack counter + smoothed gain.
	double calc_gain(const double& x) {

		if (this->log)
			return calc_gain_db(x);
		else
			return calc_gain_lin(x);
	}

private:
	double calc_gain_db(const double& x) {
		double signal = std::abs(x);
		signal = gain_to_db(signal);

		double tmp = (signal > this->threshold_db) ? 1.0 : floor_db;

		if (tmp <= last_gain) {
			if (attack_counter > t_hold) {
				tmp = this->a_atk * last_gain + this->a_atk2 * tmp;
			}
			else {
				tmp = last_gain;
				attack_counter += this->dt * 1e3;
			}
		}
		else {
			tmp = this->a_rlse * last_gain + this->a_rlse2 * tmp;
			attack_counter = 0.0;
		}
		this->last_gain = tmp;


		return  db_to_gain(tmp);


	}
	double calc_gain_lin(const double& x) {
		double signal = std::abs(x);
		double tmp = (signal > this->threshold) ? 1.0 : floor;

		if (tmp <= last_gain) {
			if (attack_counter > t_hold) {
				tmp = this->a_atk * last_gain + this->a_atk2 * tmp;
			}
			else {
				tmp = last_gain;
				attack_counter += this->dt * 1e3;
			}
		}
		else {
			tmp = this->a_rlse * last_gain + this->a_rlse2 * tmp;
			attack_counter = 0.0;
		}
		this->last_gain = tmp;


		return  tmp;
	}
	double t_atk, t_rlse, t_hold;
	double a_atk, a_rlse, a_atk2, a_rlse2;
	double attack_counter;
	double fs,dt;
	double threshold, floor,threshold_db,floor_db;
	double last_gain,last_gain_db;
	bool log;
	void recalcConstants() {
		this->a_atk = std::exp(-std::log(9) * 1.0e3 / (this->t_atk * this->fs));
		this->a_rlse = std::exp(-std::log(9) * 1.0e3 / (this->t_rlse * this->fs));

		this->a_atk2 = 1.0 - this->a_atk;
		this->a_rlse2 = 1.0 - this->a_rlse;
		this->dt = 1.0 / this->fs;
	}
};

