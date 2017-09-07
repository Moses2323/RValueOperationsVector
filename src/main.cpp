#include <iostream>
#include <string>

#include "smallvec.h"

using std::cout;
using std::cerr;
using std::endl;

void test_usual_functions(){
	cout << "START USUAL FUNCTIONS TEST" << endl;

	size_t N = 7;
	SmallVector<short> vec1(N);
	SmallVector<short> vec2(N);

	for(size_t i=0; i < N; ++i){
		vec1[i] = i;
		vec2[i] = i*10;
	}
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	SmallVector<short> vec3(vec1);
	cout << "vec3 (copy vec1) = " << vec3 << endl;
	cout << "vec1 = " << vec1 << endl << endl;

	SmallVector<short> vec4(std::move(vec3));
	cout << "vec4 (copy&& vec3) = " << vec4 << endl;
	cout << "vec3 = " << vec3 << endl << endl;

	cout << "vec1 += vec2 : " << (vec1 += vec2) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	cout << "vec1 + vec2 : " << vec1 + vec2 << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl << endl;

	vec3.resize(N);
	for(size_t i=0; i < N; ++i){
		vec3[i] = i/2;
	}

	vec4.clean();

	cout << "END OF USUAL FUNCTIONS TEST" << endl;
}

void test_plus(){
	cout << "START PLUS TEST" << endl;

	size_t N = 7;
	SmallVector<short> vec1(N);
	SmallVector<short> vec2(N);

	for(size_t i=0; i < N; ++i){
		vec1[i] = i;
		vec2[i] = i*10;
	}
	SmallVector<short> vec3(N);
	SmallVector<short> vec4;
	for(size_t i=0; i < vec3.size(); ++i){
		vec3[i] = i/2;
	}

	cout << "\tSTRANGE ARYTHMETICS:" << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "vec3 = " << vec3 << endl;
	cout << "vec4 = " << vec4 << endl;
	vec4 = vec1 + vec2 + vec3;
	cout << "vec1 + vec2 + vec3 : " << vec4 << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "vec3 = " << vec3 << endl;
	cout << "vec4 = " << vec4 << endl;
	cout << endl;

	vec4.clean();
	cout << endl;

	vec4 = std::move(std::move(vec1 + vec2) + vec3);
	cout << "std::move(std::move(vec1 + vec2) + vec3) : " << vec4 << endl;
	cout << "END OF PLUS TEST" << endl;
}

int main() {
	test_usual_functions();
	cout << "--------------------------------------------------" << endl;
	test_plus();

	auto func = [](double a1, double a2) -> double{
		return a1 + a2;
	};

	double f3 = func(3,4);
	cout << f3 << endl;

	return 0;
}
