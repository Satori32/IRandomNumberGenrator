#include <iostream>
#include <random>
#include <cstdint>
#include <memory>
#include <limits>

//big plan is fall to like a javascript.lololololololol.

#define interface struct

interface IRNG
{
	typedef std::uintmax_t result_type;//i need cut this.
	typedef std::intmax_t param_type;//i need cut this.
	static result_type max() { return std::numeric_limits<result_type>::max(); }//i need cut this.
	static result_type min() { return std::numeric_limits<result_type>::min(); }//i need cut this.

	virtual result_type operator ()() = 0;
	virtual bool SetSeed(param_type) = 0;
	typedef std::shared_ptr<IRNG> SharedRNG;
};

class MersenneTwister :public IRNG {

	bool SetSeed(IRNG::param_type N) {
		MT.seed(N);
		return true;
	}
	IRNG::result_type operator()() {
		return MT();
	}


protected:
	std::mt19937 MT;
};
class MinStdRand :public IRNG {

	bool SetSeed(IRNG::param_type N) {
		MSD.seed(N);
		return true;
	}
	IRNG::result_type operator()() {
		return MSD();
	}


protected:
	std::minstd_rand MSD;
};

class KnuthB :public IRNG {

	bool SetSeed(IRNG::param_type N) {
		KB.seed(N);
		return true;
	}
	IRNG::result_type operator()() {
		return KB();
	}


protected:
	std::knuth_b KB;
};

std::intmax_t Dice(std::uintmax_t Roll,std::uintmax_t Max, std::uintmax_t Add, IRNG& R) {

	std::intmax_t N = 0;
	std::uniform_int_distribution<std::intmax_t> UI(0, Max);

	for (std::size_t i = 0; i < Roll; i++) {
		N += UI(R);
	}

	return N + Add;

}

int main() {
	IRNG::SharedRNG R = std::make_shared<MersenneTwister>();

	std::intmax_t N = 0;

	std::uintmax_t Roll = 3;
	std::uint64_t Max = 12;
	std::uintmax_t Add = 4;

	N = Dice(Roll, Max, Add, (*R));
	std::cout << N << std::endl;
	/**/
	R = std::make_shared<MinStdRand>();

	N = Dice(Roll, Max, Add, (*R));
	std::cout << N << std::endl;

	R = std::make_shared<KnuthB>();

	N = Dice(Roll, Max, Add, (*R));
	std::cout << N << std::endl;
	/**/
	return 0;
}