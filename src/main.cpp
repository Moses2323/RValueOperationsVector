#include "smallvec.h"

#include <iostream>
#include <string>
#include <vector>
#include <valarray>

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

	SmallVector<short> vec5(N);
	for(size_t i=0; i < N; ++i){
		vec5[i] = i + 2;
	}
	cout << "vec5 = " << vec5 << endl;
	vec5.resize(N+3);
	cout << "vec5 with resize N+3 = " << vec5 << endl;
	vec5.resize(N/2);
	cout << "vec5 with resize N/2 = " << vec5 << endl;
	vec5.resize(0);
	cout << "vec5 with resize(0) = " << vec5 << endl;

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

void test_unary_minus(){
	cout << "START UNARY MINUS TEST" << endl;

	size_t N = 7;
	SmallVector<int> vec1(N);
	for(size_t i=0; i < vec1.size(); ++i)
		vec1[i] = i*2 + 1;

	cout << "vec1 = " << vec1 << endl;
	cout << "-vec1 = " << -vec1 << endl << endl;

	SmallVector<int> vec2;
	cout << "vec2 = " << vec2 << endl;
	vec2 = -vec1;
	cout << "vec1 = " << vec1 << endl;
	cout << "after vec2 = -vec1 : " << vec2 << endl << endl;

	for(size_t i=0; i < vec2.size(); ++i)
		vec2[i] = i;

	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	vec2 = -std::move(vec1);
	cout << "after vec2 = -std::move(vec1):" << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;

	cout << "END OF UNARY MINUS TEST" << endl;
}

void test_multiply(){
	cout << "START MULTIPLY TEST" << endl;

	size_t N = 7;
	SmallVector<double> vec1(N);
	for(size_t i=0; i < N; ++i)
		vec1[i] = i + 1;

	SmallVector<double> vec2(N);
	for(size_t i=0; i < N ; ++i)
		vec2[i] = 10 - i;

	double aud = 0.1;
	int aui = 5;

	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;
	cout << "aud = " << aud << endl;
	cout << "aui = " << aui << endl << endl;

	cout << "(vec1 *= aud) : " << (vec1 *= aud) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "aud = " << aud << endl << endl;

	cout << "(vec1 *= aui) : " << (vec1 *= aui) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "aui = " << aui << endl << endl;

	cout << "(vec1 *= vec2) : " << (vec1 *= vec2) << endl;
	cout << "vec1 = " << vec1 << endl;
	cout << "vec2 = " << vec2 << endl;

	cout << "END OF MULTIPLY TEST" << endl;
}

int main() {
	test_usual_functions();
	cout << "--------------------------------------------------" << endl;
	test_plus();
	cout << "--------------------------------------------------" << endl;
	test_unary_minus();
	cout << "--------------------------------------------------" << endl;
	test_multiply();
	return 0;
}
